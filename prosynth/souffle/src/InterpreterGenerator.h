/*
 * Souffle - A Datalog Compiler
 * Copyright (c) 2019, The Souffle Developers. All rights reserved.
 * Licensed under the Universal Permissive License v 1.0 as shown at:
 * - https://opensource.org/licenses/UPL
 * - <souffle root>/licenses/SOUFFLE-UPL.txt
 */

/************************************************************************
 *
 * @file InterpreterGenerator.h
 *
 * Declares the Interpreter Generator class. The generator takes an entry
 * of the RAM program and translate it into an executable InterpreterNode representation
 * with environment symbol binding in each node.
 ***********************************************************************/

#pragma once

#include "InterpreterNode.h"
#include "InterpreterPreamble.h"
#include "InterpreterRecords.h"
#include "RamIndexAnalysis.h"
#include "RamVisitor.h"
#include <memory>

namespace souffle {

/*
 * @class NodeGenerator
 * @brief Generate an executable InterpreterNode tree based on the RAM tree.
 *        Each node contains run time information which is necessary for InterpreterEngine to interpreter.
 */
class NodeGenerator : public RamVisitor<std::unique_ptr<InterpreterNode>> {
    using NodePtr = std::unique_ptr<InterpreterNode>;
    using NodePtrVec = std::vector<NodePtr>;

public:
    NodeGenerator(RamIndexAnalysis* isa) : isa(isa) {}

    /**
     * @brief Generate the tree based on given entry.
     * Return a NodePtr to the root.
     */
    NodePtr generateTree(const RamNode& root) {
        // Encode all relation, indexPos and viewId.
        visitDepthFirst(root, [&](const RamNode& node) {
            if (dynamic_cast<const RamQuery*>(&node) != nullptr) {
                newQueryBlock();
            }
            if (const auto* create = dynamic_cast<const RamCreate*>(&node)) {
                encodeRelation(create->getRelation());
            }
            if (const auto* indexSearch = dynamic_cast<const RamIndexOperation*>(&node)) {
                encodeIndexPos(*indexSearch);
                encodeView(indexSearch);
            } else if (const auto* exists = dynamic_cast<const RamExistenceCheck*>(&node)) {
                encodeIndexPos(*exists);
                encodeView(exists);
            } else if (const auto* provExists = dynamic_cast<const RamProvenanceExistenceCheck*>(&node)) {
                encodeIndexPos(*provExists);
                encodeView(provExists);
            }
        });
        // Parse program
        return visit(root);
    }

    NodePtr visitNumber(const RamNumber& num) override {
        return std::make_unique<InterpreterNode>(I_Number, &num);
    }

    NodePtr visitTupleElement(const RamTupleElement& access) override {
        return std::make_unique<InterpreterNode>(I_TupleElement, &access);
    }

    NodePtr visitAutoIncrement(const RamAutoIncrement& inc) override {
        return std::make_unique<InterpreterNode>(I_AutoIncrement, &inc);
    }

    NodePtr visitIntrinsicOperator(const RamIntrinsicOperator& op) override {
        NodePtrVec children;
        for (const auto& arg : op.getArguments()) {
            children.push_back(visit(arg));
        }
        return std::make_unique<InterpreterNode>(I_IntrinsicOperator, &op, std::move(children));
    }

    NodePtr visitUserDefinedOperator(const RamUserDefinedOperator& op) override {
        NodePtrVec children;
        for (const auto& arg : op.getArguments()) {
            children.push_back(visit(arg));
        }
        return std::make_unique<InterpreterNode>(I_UserDefinedOperator, &op, std::move(children));
    }

    NodePtr visitPackRecord(const RamPackRecord& pr) override {
        NodePtrVec children;
        for (const auto& arg : pr.getArguments()) {
            children.push_back(visit(arg));
        }
        return std::make_unique<InterpreterNode>(I_PackRecord, &pr, std::move(children));
    }

    NodePtr visitSubroutineArgument(const RamSubroutineArgument& arg) override {
        return std::make_unique<InterpreterNode>(I_SubroutineArgument, &arg);
    }

    // -- connectors operators --
    NodePtr visitTrue(const RamTrue& ltrue) override {
        return std::make_unique<InterpreterNode>(I_True, &ltrue);
    }

    NodePtr visitFalse(const RamFalse& lfalse) override {
        return std::make_unique<InterpreterNode>(I_False, &lfalse);
    }

    NodePtr visitConjunction(const RamConjunction& conj) override {
        NodePtrVec children;
        children.push_back(visit(conj.getLHS()));
        children.push_back(visit(conj.getRHS()));
        return std::make_unique<InterpreterNode>(I_Conjunction, &conj, std::move(children));
    }

    NodePtr visitNegation(const RamNegation& neg) override {
        NodePtrVec children;
        children.push_back(visit(neg.getOperand()));
        return std::make_unique<InterpreterNode>(I_Negation, &neg, std::move(children));
    }

    NodePtr visitEmptinessCheck(const RamEmptinessCheck& emptiness) override {
        std::vector<size_t> data;
        data.push_back(encodeRelation(emptiness.getRelation()));
        return std::make_unique<InterpreterNode>(I_EmptinessCheck, &emptiness, NodePtrVec{}, std::move(data));
    }

    NodePtr visitExistenceCheck(const RamExistenceCheck& exists) override {
        NodePtrVec children;
        for (const auto& value : exists.getValues()) {
            children.push_back(visit(value));
        }
        std::vector<size_t> data;
        data.push_back(encodeRelation(exists.getRelation()));
        data.push_back(encodeView(&exists));
        return std::make_unique<InterpreterNode>(
                I_ExistenceCheck, &exists, std::move(children), std::move(data));
    }

    NodePtr visitProvenanceExistenceCheck(const RamProvenanceExistenceCheck& provExists) override {
        NodePtrVec children;
        for (const auto& value : provExists.getValues()) {
            children.push_back(visit(value));
        }
        std::vector<size_t> data;
        data.push_back(encodeView(&provExists));
        return std::make_unique<InterpreterNode>(
                I_ProvenanceExistenceCheck, &provExists, std::move(children), std::move(data));
    }

    // -- comparison operators --
    NodePtr visitConstraint(const RamConstraint& relOp) override {
        NodePtrVec children;
        children.push_back(visit(relOp.getLHS()));
        children.push_back(visit(relOp.getRHS()));
        return std::make_unique<InterpreterNode>(I_Constraint, &relOp, std::move(children));
    }

    NodePtr visitNestedOperation(const RamNestedOperation& nested) override {
        return visit(nested.getOperation());
    }

    NodePtr visitTupleOperation(const RamTupleOperation& search) override {
        NodePtrVec children;
        children.push_back(visit(search.getOperation()));
        return std::make_unique<InterpreterNode>(I_TupleOperation, &search, std::move(children));
    }

    NodePtr visitScan(const RamScan& scan) override {
        NodePtrVec children;
        children.push_back(visitTupleOperation(scan));
        std::vector<size_t> data;
        data.push_back(encodeRelation(scan.getRelation()));
        return std::make_unique<InterpreterNode>(I_Scan, &scan, std::move(children), std::move(data));
    }

    NodePtr visitParallelScan(const RamParallelScan& pScan) override {
        NodePtrVec children;
        children.push_back(visitTupleOperation(pScan));
        std::vector<size_t> data;
        data.push_back((encodeRelation(pScan.getRelation())));
        auto res = std::make_unique<InterpreterNode>(
                I_ParallelScan, &pScan, std::move(children), std::move(data));
        res->setPreamble(parentQueryPreamble);
        return res;
    }

    NodePtr visitIndexScan(const RamIndexScan& scan) override {
        NodePtrVec children;
        for (const auto& value : scan.getRangePattern()) {
            children.push_back(visit(value));
        }
        children.push_back(visitTupleOperation(scan));
        std::vector<size_t> data;
        data.push_back((encodeView(&scan)));
        return std::make_unique<InterpreterNode>(I_IndexScan, &scan, std::move(children), std::move(data));
    }

    NodePtr visitParallelIndexScan(const RamParallelIndexScan& piscan) override {
        NodePtrVec children;
        for (const auto& value : piscan.getRangePattern()) {
            children.push_back(visit(value));
        }
        children.push_back(visitTupleOperation(piscan));
        std::vector<size_t> data;
        data.push_back((encodeRelation(piscan.getRelation())));
        data.push_back((encodeIndexPos(piscan)));
        auto res = std::make_unique<InterpreterNode>(
                I_ParallelIndexScan, &piscan, std::move(children), std::move(data));
        res->setPreamble(parentQueryPreamble);
        return res;
    }

    NodePtr visitChoice(const RamChoice& choice) override {
        NodePtrVec children;
        children.push_back(visit(choice.getCondition()));
        children.push_back(visitTupleOperation(choice));
        std::vector<size_t> data;
        data.push_back((encodeRelation(choice.getRelation())));
        return std::make_unique<InterpreterNode>(I_Choice, &choice, std::move(children), std::move(data));
    }

    NodePtr visitParallelChoice(const RamParallelChoice& pchoice) override {
        NodePtrVec children;
        children.push_back(visit(pchoice.getCondition()));
        children.push_back(visitTupleOperation(pchoice));
        std::vector<size_t> data;
        data.push_back(encodeRelation(pchoice.getRelation()));
        auto res = std::make_unique<InterpreterNode>(
                I_ParallelChoice, &pchoice, std::move(children), std::move(data));
        res->setPreamble(parentQueryPreamble);
        return res;
    }

    NodePtr visitIndexChoice(const RamIndexChoice& choice) override {
        NodePtrVec children;
        for (const auto& value : choice.getRangePattern()) {
            children.push_back(visit(value));
        }
        children.push_back(visit(choice.getCondition()));
        children.push_back(visitTupleOperation(choice));
        std::vector<size_t> data;
        data.push_back((encodeView(&choice)));
        return std::make_unique<InterpreterNode>(
                I_IndexChoice, &choice, std::move(children), std::move(data));
    }

    NodePtr visitParallelIndexChoice(const RamParallelIndexChoice& ichoice) override {
        NodePtrVec children;
        for (const auto& value : ichoice.getRangePattern()) {
            children.push_back(visit(value));
        }
        children.push_back(visit(ichoice.getCondition()));
        children.push_back(visit(ichoice.getOperation()));
        std::vector<size_t> data;
        data.push_back((encodeRelation(ichoice.getRelation())));
        data.push_back((encodeIndexPos(ichoice)));
        auto res = std::make_unique<InterpreterNode>(
                I_ParallelIndexChoice, &ichoice, std::move(children), std::move(data));
        res->setPreamble(parentQueryPreamble);
        return res;
    }

    NodePtr visitUnpackRecord(const RamUnpackRecord& lookup) override {  // get reference
        NodePtrVec children;
        children.push_back(visit(lookup.getExpression()));
        children.push_back(visitTupleOperation(lookup));
        createRecordMap(lookup.getArity());
        return std::make_unique<InterpreterNode>(I_UnpackRecord, &lookup, std::move(children));
    }

    NodePtr visitAggregate(const RamAggregate& aggregate) override {
        NodePtrVec children;
        children.push_back(visit(aggregate.getCondition()));
        children.push_back(visit(aggregate.getExpression()));
        children.push_back(visitTupleOperation(aggregate));
        std::vector<size_t> data;
        data.push_back((encodeRelation(aggregate.getRelation())));
        return std::make_unique<InterpreterNode>(
                I_Aggregate, &aggregate, std::move(children), std::move(data));
    }

    NodePtr visitIndexAggregate(const RamIndexAggregate& aggregate) override {
        NodePtrVec children;
        for (const auto& value : aggregate.getRangePattern()) {
            children.push_back(visit(value));
        }
        children.push_back(visit(aggregate.getCondition()));
        children.push_back(visit(aggregate.getExpression()));
        children.push_back(visitTupleOperation(aggregate));
        std::vector<size_t> data;
        data.push_back((encodeRelation(aggregate.getRelation())));
        data.push_back((encodeView(&aggregate)));
        return std::make_unique<InterpreterNode>(
                I_IndexAggregate, &aggregate, std::move(children), std::move(data));
    }

    NodePtr visitBreak(const RamBreak& breakOp) override {
        NodePtrVec children;
        children.push_back(visit(breakOp.getCondition()));
        children.push_back(visit(breakOp.getOperation()));
        return std::make_unique<InterpreterNode>(I_Break, &breakOp, std::move(children));
    }

    NodePtr visitFilter(const RamFilter& filter) override {
        NodePtrVec children;
        children.push_back(visit(filter.getCondition()));
        children.push_back(visit(filter.getOperation()));
        return std::make_unique<InterpreterNode>(I_Filter, &filter, std::move(children));
    }

    NodePtr visitProject(const RamProject& project) override {
        NodePtrVec children;
        for (const auto& value : project.getValues()) {
            children.push_back(visit(value));
        }
        std::vector<size_t> data;
        data.push_back((encodeRelation(project.getRelation())));
        return std::make_unique<InterpreterNode>(I_Project, &project, std::move(children), std::move(data));
    }

    // -- return from subroutine --
    NodePtr visitSubroutineReturnValue(const RamSubroutineReturnValue& ret) override {
        NodePtrVec children;
        for (const auto& value : ret.getValues()) {
            children.push_back(visit(value));
        }
        return std::make_unique<InterpreterNode>(I_SubroutineReturnValue, &ret, std::move(children));
    }

    NodePtr visitSequence(const RamSequence& seq) override {
        NodePtrVec children;
        for (const auto& value : seq.getStatements()) {
            children.push_back(visit(value));
        }
        return std::make_unique<InterpreterNode>(I_Sequence, &seq, std::move(children));
    }

    NodePtr visitParallel(const RamParallel& parallel) override {
        // Parallel statements are executed in sequence for now.
        NodePtrVec children;
        for (const auto& value : parallel.getStatements()) {
            children.push_back(visit(value));
        }
        return std::make_unique<InterpreterNode>(I_Parallel, &parallel, std::move(children));
    }

    NodePtr visitLoop(const RamLoop& loop) override {
        NodePtrVec children;
        children.push_back(visit(loop.getBody()));
        return std::make_unique<InterpreterNode>(I_Loop, &loop, std::move(children));
    }

    NodePtr visitExit(const RamExit& exit) override {
        NodePtrVec children;
        children.push_back(visit(exit.getCondition()));
        return std::make_unique<InterpreterNode>(I_Exit, &exit, std::move(children));
    }

    NodePtr visitLogRelationTimer(const RamLogRelationTimer& timer) override {
        NodePtrVec children;
        children.push_back(visit(timer.getStatement()));
        std::vector<size_t> data;
        data.push_back(encodeRelation(timer.getRelation()));
        return std::make_unique<InterpreterNode>(
                I_LogRelationTimer, &timer, std::move(children), std::move(data));
    }

    NodePtr visitLogTimer(const RamLogTimer& timer) override {
        NodePtrVec children;
        children.push_back(visit(timer.getStatement()));
        return std::make_unique<InterpreterNode>(I_LogTimer, &timer, std::move(children));
    }

    NodePtr visitDebugInfo(const RamDebugInfo& dbg) override {
        NodePtrVec children;
        children.push_back(visit(dbg.getStatement()));
        return std::make_unique<InterpreterNode>(I_DebugInfo, &dbg, std::move(children));
    }

    NodePtr visitStratum(const RamStratum& stratum) override {
        NodePtrVec children;
        children.push_back(visit(stratum.getBody()));
        return std::make_unique<InterpreterNode>(I_Stratum, &stratum, std::move(children));
    }

    NodePtr visitCreate(const RamCreate& create) override {
        std::vector<size_t> data;
        data.push_back((encodeRelation(create.getRelation())));
        return std::make_unique<InterpreterNode>(I_Create, &create, NodePtrVec{}, std::move(data));
    }

    NodePtr visitClear(const RamClear& clear) override {
        std::vector<size_t> data;
        data.push_back((encodeRelation(clear.getRelation())));
        return std::make_unique<InterpreterNode>(I_Clear, &clear, NodePtrVec{}, std::move(data));
    }

    NodePtr visitDrop(const RamDrop& drop) override {
        std::vector<size_t> data;
        data.push_back((encodeRelation(drop.getRelation())));
        return std::make_unique<InterpreterNode>(I_Drop, &drop, NodePtrVec{}, std::move(data));
    }

    NodePtr visitLogSize(const RamLogSize& size) override {
        std::vector<size_t> data;
        data.push_back((encodeRelation(size.getRelation())));
        return std::make_unique<InterpreterNode>(I_LogSize, &size, NodePtrVec{}, std::move(data));
    }

    NodePtr visitLoad(const RamLoad& load) override {
        std::vector<size_t> data;
        data.push_back((encodeRelation(load.getRelation())));
        return std::make_unique<InterpreterNode>(I_Load, &load, NodePtrVec{}, std::move(data));
    }

    NodePtr visitStore(const RamStore& store) override {
        std::vector<size_t> data;
        data.push_back((encodeRelation(store.getRelation())));
        return std::make_unique<InterpreterNode>(I_Store, &store, NodePtrVec{}, std::move(data));
    }

    NodePtr visitFact(const RamFact& fact) override {
        NodePtrVec children;
        for (auto& val : fact.getValues()) {
            children.push_back(visit(val));
        }
        std::vector<size_t> data;
        data.push_back((encodeRelation(fact.getRelation())));
        return std::make_unique<InterpreterNode>(I_Fact, &fact, std::move(children), std::move(data));
    }

    NodePtr visitQuery(const RamQuery& query) override {
        std::shared_ptr<InterpreterPreamble> preamble = std::make_shared<InterpreterPreamble>();
        parentQueryPreamble = preamble;
        // split terms of conditions of outer-most filter operation
        // into terms that require a context and terms that
        // do not require a view
        const RamOperation* next = &query.getOperation();
        std::vector<const RamCondition*> freeOfView;
        if (const auto* filter = dynamic_cast<const RamFilter*>(&query.getOperation())) {
            next = &filter->getOperation();
            // Check terms of outer filter operation whether they can be pushed before
            // the view-generation for speed improvements
            auto conditions = toConjunctionList(&filter->getCondition());
            for (auto const& cur : conditions) {
                bool needView = false;
                visitDepthFirst(*cur, [&](const RamNode& node) {
                    if (requireView(&node)) {
                        needView = true;
                        const auto& rel = getRelationRefForView(&node);
                        preamble->addViewInfoForFilter(
                                encodeRelation(rel), indexTable[&node], encodeView(&node));
                    }
                });

                if (needView == true) {
                    preamble->addViewOperationForFilter(visit(*cur));
                } else {
                    preamble->addViewFreeOperationForFilter(visit(*cur));
                }
            }
        }

        visitDepthFirst(*next, [&](const RamNode& node) {
            if (requireView(&node) == true) {
                const auto& rel = getRelationRefForView(&node);
                preamble->addViewInfoForNested(encodeRelation(rel), indexTable[&node], encodeView(&node));
            };
        });

        visitDepthFirst(*next, [&](const RamAbstractParallel& node) { preamble->isParallel = true; });

        NodePtrVec children;
        children.push_back(visit(*next));

        auto res = std::make_unique<InterpreterNode>(I_Query, &query, std::move(children));
        res->setPreamble(parentQueryPreamble);
        return res;
    }

    NodePtr visitMerge(const RamMerge& merge) override {
        std::vector<size_t> data;
        data.push_back((encodeRelation(merge.getFirstRelation())));
        data.push_back(encodeRelation(merge.getSecondRelation()));
        return std::make_unique<InterpreterNode>(I_Merge, &merge, NodePtrVec{}, std::move(data));
    }

    NodePtr visitSwap(const RamSwap& swap) override {
        std::vector<size_t> data;
        data.push_back((encodeRelation(swap.getFirstRelation())));
        data.push_back((encodeRelation(swap.getSecondRelation())));
        return std::make_unique<InterpreterNode>(I_Swap, &swap, NodePtrVec{}, std::move(data));
    }

    NodePtr visitUndefValue(const RamUndefValue& undef) override {
        return nullptr;
    }

    NodePtr visitNode(const RamNode& node) override {
        std::cerr << "Unsupported node type: " << typeid(node).name() << "\n";
        assert(false && "Unsupported Node Type!");
        return 0;
    }

private:
    /** Environment encoding, store a mapping from RamNode to its operation index id. */
    std::unordered_map<const RamNode*, size_t> indexTable;
    /** Used by index encoding */
    RamIndexAnalysis* isa;
    /** Points to the current preamble during the generation.  It is used to passing preamble between parent
     * query and its nested parallel operation. */
    std::shared_ptr<InterpreterPreamble> parentQueryPreamble = nullptr;
    /** Next available location to encode View */
    size_t viewId = 0;
    /** Next available location to encode a relation */
    size_t relId = 0;
    /** Environment encoding, store a mapping from RamNode to its View id. */
    std::unordered_map<const RamNode*, size_t> viewTable;
    /** Environment encoding, store a mapping from RamRelation to its id */
    std::unordered_map<const RamRelation*, size_t> relTable;

    /** @brief Reset view allocation system, since view's life time is within each query. */
    void newQueryBlock() {
        viewTable.clear();
        viewId = 0;
    }

    /** @brief Get a valid relation id for encoding */
    size_t getNewRelId() {
        return relId++;
    }

    /** @brief Get a valid view id for encoding */
    size_t getNextViewId() {
        return viewId++;
    }

    /** @brief Return operation index id from the result of indexAnalysis */
    template <class RamNode>
    size_t encodeIndexPos(RamNode& node) {
        const MinIndexSelection& orderSet = isa->getIndexes(node.getRelation());
        SearchSignature signature = isa->getSearchSignature(&node);
        // A zero signature is equivalent as a full order signature.
        if (signature == 0) {
            signature = (1 << node.getRelation().getArity()) - 1;
        }
        auto i = orderSet.getLexOrderNum(signature);
        indexTable[&node] = i;
        return i;
    };

    /** @brief Encode and return the View id of an operation. */
    size_t encodeView(const RamNode* node) {
        auto pos = viewTable.find(node);
        if (pos != viewTable.end()) {
            return pos->second;
        }
        size_t id = getNextViewId();
        viewTable[node] = id;
        return id;
    }

    /** @brief Encode and return the relation id */
    size_t encodeRelation(const RamRelation& rel) {
        auto pos = relTable.find(&rel);
        if (pos != relTable.end()) {
            return pos->second;
        }
        size_t id = getNewRelId();
        relTable[&rel] = id;
        return id;
    }

    /**
     * @brief Find all operations under the root node that requires a view.
     * Return a list of InterpreterNodes.
     */
    NodePtrVec findAllViews(const RamNode& node) {
        NodePtrVec res;
        visitDepthFirst(node, [&](const RamNode& node) {
            if (requireView(&node) == true) {
                res.push_back(visit(node));
            };
        });
        return res;
    }

    /**
     * Return true if the given operation requires a view.
     */
    bool requireView(const RamNode* node) {
        if (dynamic_cast<const RamAbstractExistenceCheck*>(node) != nullptr) {
            return true;
        } else if (dynamic_cast<const RamIndexOperation*>(node) != nullptr) {
            return true;
        }
        return false;
    }

    /**
     * @brief Return the associated relation of a operation which requires a view.
     * This function assume the operation does requires a view.
     */
    const RamRelation& getRelationRefForView(const RamNode* node) {
        if (const RamAbstractExistenceCheck* exist = dynamic_cast<const RamAbstractExistenceCheck*>(node)) {
            return exist->getRelation();
        } else if (const RamIndexOperation* index = dynamic_cast<const RamIndexOperation*>(node)) {
            return index->getRelation();
        }
        assert(false && "The RamNode does not require a view.");
    }

    /**
     * @brief Convert terms of a conjunction to a list
     *
     * Convert a condition of the format C1 /\ C2 /\ ... /\ Cn
     * to a list {C1, C2, ..., Cn}.
     */
    inline std::vector<const RamCondition*> toConjunctionList(const RamCondition* condition) {
        std::vector<const RamCondition*> list;
        std::stack<const RamCondition*> stack;
        if (condition != nullptr) {
            stack.push(condition);
            while (!stack.empty()) {
                condition = stack.top();
                stack.pop();
                if (const auto* ramConj = dynamic_cast<const RamConjunction*>(condition)) {
                    stack.push(&ramConj->getLHS());
                    stack.push(&ramConj->getRHS());
                } else {
                    list.emplace_back(condition);
                }
            }
        }
        return list;
    }
};
}  // namespace souffle
