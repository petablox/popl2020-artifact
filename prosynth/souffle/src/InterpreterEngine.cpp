/*
 * Souffle - A Datalog Compiler
 * Copyright (c) 2019, The Souffle Developers. All rights reserved.
 * Licensed under the Universal Permissive License v 1.0 as shown at:
 * - https://opensource.org/licenses/UPL
 * - <souffle root>/licenses/SOUFFLE-UPL.txt
 */

/************************************************************************
 *
 * @file InterpreterEngine.cpp
 *
 * Define the Interpreter Engine class.
 ***********************************************************************/

#include "InterpreterEngine.h"
#include "IOSystem.h"
#include "InterpreterGenerator.h"
#include "InterpreterRecords.h"
#include "Logger.h"
#include "SignalHandler.h"
#include <cassert>
#include <csignal>
#include <regex>
#include <ffi.h>

namespace souffle {

void InterpreterEngine::createRelation(
        const RamRelation& id, const MinIndexSelection& orderSet, const size_t idx) {
    RelationHandle res;
    if (relations.size() < idx + 1) {
        relations.resize(idx + 1);
    }
    if (id.getRepresentation() == RelationRepresentation::EQREL) {
        res = std::make_unique<InterpreterEqRelation>(
                id.getArity(), id.getName(), std::vector<std::string>(), orderSet);
    } else {
        if (isProvenance) {
            res = std::make_unique<InterpreterRelation>(id.getArity(), id.getName(),
                    std::vector<std::string>(), orderSet, createBTreeProvenanceIndex);
        } else {
            res = std::make_unique<InterpreterRelation>(
                    id.getArity(), id.getName(), std::vector<std::string>(), orderSet);
        }
    }
    std::swap(relations[idx], res);
}

InterpreterRelation& InterpreterEngine::getRelation(const size_t idx) {
    return *relations[idx].get();
}

InterpreterEngine::RelationHandle& InterpreterEngine::getRelationHandle(const size_t idx) {
    return relations[idx];
}

void InterpreterEngine::dropRelation(const size_t relId) {
    relations[relId].reset(nullptr);
}

void InterpreterEngine::swapRelation(const size_t ramRel1, const size_t ramRel2) {
    RelationHandle& rel1 = getRelationHandle(ramRel1);
    RelationHandle& rel2 = getRelationHandle(ramRel2);
    std::swap(rel1, rel2);
}

int InterpreterEngine::incCounter() {
    return counter++;
}

SymbolTable& InterpreterEngine::getSymbolTable() {
    return tUnit.getSymbolTable();
}

RamTranslationUnit& InterpreterEngine::getTranslationUnit() {
    return tUnit;
}

void* InterpreterEngine::getMethodHandle(const std::string& method) {
    // load DLLs (if not done yet)
    for (void* libHandle : loadDLL()) {
        auto* methodHandle = dlsym(libHandle, method.c_str());
        if (methodHandle != nullptr) {
            return methodHandle;
        }
    }
    return nullptr;
}

std::vector<InterpreterEngine::RelationHandle>& InterpreterEngine::getRelationMap() {
    return relations;
}

const std::vector<void*>& InterpreterEngine::loadDLL() {
    if (!dll.empty()) {
        return dll;
    }

    if (!Global::config().has("libraries")) {
        Global::config().set("libraries", "functors");
    }
    if (!Global::config().has("library-dir")) {
        Global::config().set("library-dir", ".");
    }
    for (const std::string& library : splitString(Global::config().get("libraries"), ' ')) {
        // The library may be blank
        if (library.empty()) {
            continue;
        }
        auto paths = splitString(Global::config().get("library-dir"), ' ');
        // Set up our paths to have a library appended
        for (std::string& path : paths) {
            if (path.back() != '/') {
                path += '/';
            }
        }

        if (library.find('/') != std::string::npos) {
            paths.clear();
        }

        paths.push_back("");

        void* tmp = nullptr;
        for (const std::string& path : paths) {
            std::string fullpath = path + "lib" + library + ".so";
            tmp = dlopen(fullpath.c_str(), RTLD_LAZY);
            if (tmp != nullptr) {
                dll.push_back(tmp);
                break;
            }
        }
    }

    return dll;
}

size_t InterpreterEngine::getIterationNumber() const {
    return iteration;
}
void InterpreterEngine::incIterationNumber() {
    ++iteration;
}
void InterpreterEngine::resetIterationNumber() {
    iteration = 0;
}

void InterpreterEngine::executeMain() {
    SignalHandler::instance()->set();
    if (Global::config().has("verbose")) {
        SignalHandler::instance()->enableLogging();
    }
    auto* program = tUnit.getProgram()->getMain();
    auto entry = generator.generateTree(*program);
    InterpreterContext ctxt;
    if (!profileEnabled) {
        InterpreterContext ctxt;
        execute(entry.get(), ctxt);
    } else {
        ProfileEventSingleton::instance().setOutputFile(Global::config().get("profile"));
        // Prepare the frequency table for threaded use
        visitDepthFirst(*program, [&](const RamTupleOperation& node) {
            if (!node.getProfileText().empty()) {
                frequencies.emplace(node.getProfileText(), std::deque<std::atomic<size_t>>());
            }
            frequencies[node.getProfileText()].emplace_back(0);
        });
        // Enable profiling for execution of main
        ProfileEventSingleton::instance().startTimer();
        ProfileEventSingleton::instance().makeTimeEvent("@time;starttime");
        // Store configuration
        for (const auto& cur : Global::config().data()) {
            ProfileEventSingleton::instance().makeConfigRecord(cur.first, cur.second);
        }
        // Store count of relations
        size_t relationCount = 0;
        visitDepthFirst(*program, [&](const RamCreate& create) {
            if (create.getRelation().getName()[0] != '@') {
                ++relationCount;
                reads[create.getRelation().getName()] = 0;
            }
        });
        ProfileEventSingleton::instance().makeConfigRecord("relationCount", std::to_string(relationCount));

        // Store count of rules
        size_t ruleCount = 0;
        visitDepthFirst(*program, [&](const RamQuery& rule) { ++ruleCount; });
        ProfileEventSingleton::instance().makeConfigRecord("ruleCount", std::to_string(ruleCount));

        InterpreterContext ctxt;
        execute(entry.get(), ctxt);
        ProfileEventSingleton::instance().stopTimer();
        for (auto const& cur : frequencies) {
            for (size_t i = 0; i < cur.second.size(); ++i) {
                ProfileEventSingleton::instance().makeQuantityEvent(cur.first, cur.second[i], i);
            }
        }
        for (auto const& cur : reads) {
            ProfileEventSingleton::instance().makeQuantityEvent(
                    "@relation-reads;" + cur.first, cur.second, 0);
        }
    }
    SignalHandler::instance()->reset();
}
void InterpreterEngine::executeSubroutine(const std::string& name, const std::vector<RamDomain>& args,
        std::vector<RamDomain>& ret, std::vector<bool>& err) {
    InterpreterContext ctxt;
    ctxt.setReturnValues(ret);
    ctxt.setReturnErrors(err);
    ctxt.setArguments(args);

    auto entry = generator.generateTree(tUnit.getProgram()->getSubroutine(name));
    execute(entry.get(), ctxt);
}

RamDomain InterpreterEngine::execute(const InterpreterNode* node, InterpreterContext& ctxt) {
#define DEBUG(Kind) std::cout << "Running Node: " << #Kind << "\n";

#define CASE(Kind)     \
    case (I_##Kind): { \
        const auto* cur = static_cast<const Ram##Kind*>(node->getShadow());

#define CASE_NO_CAST(Kind) case (I_##Kind): {
#define ESAC(Kind)                                                        \
    assert(false && "Program reach end of the scope but didn't return."); \
    }

    switch (node->getType()) {
        CASE(Number)
        return cur->getConstant();
        ESAC(Number)

        CASE(TupleElement)
        return ctxt[cur->getTupleId()][cur->getElement()];
        ESAC(TupleElement)

        CASE_NO_CAST(AutoIncrement)
        return incCounter();
        ESAC(AutoIncrement)

        CASE(IntrinsicOperator)
#define BINARY_OP(op) return execute(node->getChild(0), ctxt) op execute(node->getChild(1), ctxt)
        const auto& args = cur->getArguments();
        switch (cur->getOperator()) {
            /** Unary Functor Operators */
            case FunctorOp::ORD:
                return execute(node->getChild(0), ctxt);
            case FunctorOp::STRLEN:
                return getSymbolTable().resolve(execute(node->getChild(0), ctxt)).size();
            case FunctorOp::NEG:
                return -execute(node->getChild(0), ctxt);
            case FunctorOp::BNOT:
                return ~execute(node->getChild(0), ctxt);
            case FunctorOp::LNOT:
                return !execute(node->getChild(0), ctxt);
            case FunctorOp::TONUMBER: {
                RamDomain result = 0;
                try {
                    result = stord(getSymbolTable().resolve(execute(node->getChild(0), ctxt)));
                } catch (...) {
                    std::cerr << "error: wrong string provided by to_number(\"";
                    std::cerr << getSymbolTable().resolve(execute(node->getChild(0), ctxt));
                    std::cerr << "\") functor.\n";
                    raise(SIGFPE);
                }
                return result;
            }
            case FunctorOp::TOSTRING:
                return getSymbolTable().lookup(std::to_string(execute(node->getChild(0), ctxt)));
            /** Binary Functor Operators */
            case FunctorOp::ADD: {
                BINARY_OP(+);
            }
            case FunctorOp::SUB: {
                BINARY_OP(-);
            }
            case FunctorOp::MUL: {
                BINARY_OP(*);
            }
            case FunctorOp::DIV: {
                BINARY_OP(/);
            }
            case FunctorOp::EXP: {
                return std::pow(execute(node->getChild(0), ctxt), execute(node->getChild(1), ctxt));
            }
            case FunctorOp::MOD: {
                BINARY_OP(%);
            }
            case FunctorOp::BAND: {
                BINARY_OP(&);
            }
            case FunctorOp::BOR: {
                BINARY_OP(|);
            }
            case FunctorOp::BXOR: {
                BINARY_OP(^);
            }
            case FunctorOp::LAND: {
                BINARY_OP(&&);
            }
            case FunctorOp::LOR: {
                BINARY_OP(||);
            }
            case FunctorOp::MAX: {
                auto result = execute(node->getChild(0), ctxt);
                for (size_t i = 1; i < args.size(); i++) {
                    result = std::max(result, execute(node->getChild(i), ctxt));
                }
                return result;
            }
            case FunctorOp::MIN: {
                auto result = execute(node->getChild(0), ctxt);
                for (size_t i = 1; i < args.size(); i++) {
                    result = std::min(result, execute(node->getChild(i), ctxt));
                }
                return result;
            }
            case FunctorOp::CAT: {
                std::stringstream ss;
                for (size_t i = 0; i < args.size(); i++) {
                    ss << getSymbolTable().resolve(execute(node->getChild(i), ctxt));
                }
                return getSymbolTable().lookup(ss.str());
            }
            /** Ternary Functor Operators */
            case FunctorOp::SUBSTR: {
                auto symbol = execute(node->getChild(0), ctxt);
                const std::string& str = getSymbolTable().resolve(symbol);
                auto idx = execute(node->getChild(1), ctxt);
                auto len = execute(node->getChild(2), ctxt);
                std::string sub_str;
                try {
                    sub_str = str.substr(idx, len);
                } catch (...) {
                    std::cerr << "warning: wrong index position provided by substr(\"";
                    std::cerr << str << "\"," << (int32_t)idx << "," << (int32_t)len << ") functor.\n";
                }
                return getSymbolTable().lookup(sub_str);
            }
            /** Undefined */
            default: {
                assert(false && "unsupported operator");
                return 0;
            }
        }
        ESAC(IntrinsicOperator)

        CASE(UserDefinedOperator)
        // get name and type
        const std::string& name = cur->getName();
        const std::string& type = cur->getType();

        auto fn = reinterpret_cast<void (*)()>(getMethodHandle(name));
        if (fn == nullptr) {
            std::cerr << "Cannot find user-defined operator " << name << std::endl;
            exit(1);
        }
        // prepare dynamic call environment
        size_t arity = cur->getArgCount();
        ffi_cif cif;
        ffi_type* args[arity];
        void* values[arity];
        RamDomain intVal[arity];
        const char* strVal[arity];
        ffi_arg rc;

        /* Initialize arguments for ffi-call */
        for (size_t i = 0; i < arity; i++) {
            RamDomain arg = execute(node->getChild(i), ctxt);
            if (type[i] == 'S') {
                args[i] = &ffi_type_pointer;
                strVal[i] = getSymbolTable().resolve(arg).c_str();
                values[i] = &strVal[i];
            } else {
                args[i] = &ffi_type_uint32;
                intVal[i] = arg;
                values[i] = &intVal[i];
            }
        }

        // call external function
        if (type[arity] == 'N') {
            // Initialize for numerical return value
            if (ffi_prep_cif(&cif, FFI_DEFAULT_ABI, arity, &ffi_type_uint32, args) != FFI_OK) {
                std::cerr << "Failed to prepare CIF for user-defined operator ";
                std::cerr << name << std::endl;
                exit(1);
            }
        } else {
            // Initialize for string return value
            if (ffi_prep_cif(&cif, FFI_DEFAULT_ABI, arity, &ffi_type_pointer, args) != FFI_OK) {
                std::cerr << "Failed to prepare CIF for user-defined operator ";
                std::cerr << name << std::endl;
                exit(1);
            }
        }
        ffi_call(&cif, fn, &rc, values);
        RamDomain result;
        if (type[arity] == 'N') {
            result = ((RamDomain)rc);
        } else {
            result = getSymbolTable().lookup(((const char*)rc));
        }
        return result;
        ESAC(UserDefinedOperator)

        CASE(PackRecord)
        auto values = cur->getArguments();
        size_t arity = values.size();
        RamDomain data[arity];
        for (size_t i = 0; i < arity; ++i) {
            data[i] = execute(node->getChild(i), ctxt);
        }
        return packInterpreter(data, arity);
        ESAC(PackRecord)

        CASE(SubroutineArgument)
        return ctxt.getArgument(cur->getArgument());
        ESAC(SubroutineArgument)

        CASE_NO_CAST(True)
        return true;
        ESAC(True)

        CASE_NO_CAST(False)
        return false;
        ESAC(False)

        CASE_NO_CAST(Conjunction)
        return execute(node->getChild(0), ctxt) && execute(node->getChild(1), ctxt);
        ESAC(Conjunction)

        CASE_NO_CAST(Negation)
        return !execute(node->getChild(0), ctxt);
        ESAC(Negation)

        CASE_NO_CAST(EmptinessCheck)
        return getRelation(node->getData(0)).empty();
        ESAC(EmptinessCheck)

        CASE(ExistenceCheck)
        // construct the pattern tuple
        size_t arity = cur->getRelation().getArity();

        auto& rel = getRelation(node->getData(0));

        if (profileEnabled && !cur->getRelation().isTemp()) {
            reads[cur->getRelation().getName()]++;
        }
        // for total we use the exists test
        if (isa->isTotalSignature(cur)) {
            RamDomain tuple[arity];
            for (size_t i = 0; i < arity; i++) {
                tuple[i] = execute(node->getChild(i), ctxt);
            }
            return rel.contains(TupleRef(tuple, arity));
        }

        // for partial we search for lower and upper boundaries
        RamDomain low[arity];
        RamDomain high[arity];
        for (size_t i = 0; i < node->getChildren().size(); ++i) {
            low[i] = node->getChild(i) != nullptr ? execute(node->getChild(i), ctxt) : MIN_RAM_DOMAIN;
            high[i] = node->getChild(i) != nullptr ? low[i] : MAX_RAM_DOMAIN;
        }
        size_t viewPos = node->getData(1);
        return ctxt.getView(viewPos)->contains(TupleRef(low, arity), TupleRef(high, arity));
        ESAC(ExistenceCheck)

        CASE(ProvenanceExistenceCheck)
        // construct the pattern tuple
        size_t arity = cur->getRelation().getArity();

        // for partial we search for lower and upper boundaries
        RamDomain low[arity];
        RamDomain high[arity];
        for (size_t i = 0; i < arity - 2; i++) {
            low[i] = node->getChild(i) ? execute(node->getChild(i), ctxt) : MIN_RAM_DOMAIN;
            high[i] = node->getChild(i) ? low[i] : MAX_RAM_DOMAIN;
        }

        low[arity - 2] = MIN_RAM_DOMAIN;
        low[arity - 1] = MIN_RAM_DOMAIN;
        high[arity - 2] = MAX_RAM_DOMAIN;
        high[arity - 1] = MAX_RAM_DOMAIN;

        // obtain view
        size_t viewPos = node->getData(0);
        return ctxt.getView(viewPos)->contains(TupleRef(low, arity), TupleRef(high, arity));
        ESAC(ProvenanceExistenceCheck)

        CASE(Constraint)
        switch (cur->getOperator()) {
            case (BinaryConstraintOp::EQ):
                BINARY_OP(==);
            case (BinaryConstraintOp::NE):
                BINARY_OP(!=);
            case (BinaryConstraintOp::LT):
                BINARY_OP(<);
            case (BinaryConstraintOp::LE):
                BINARY_OP(<=);
            case (BinaryConstraintOp::GT):
                BINARY_OP(>);
            case (BinaryConstraintOp::GE):
                BINARY_OP(>=);
            case (BinaryConstraintOp::MATCH): {
                RamDomain left = execute(node->getChild(0), ctxt);
                RamDomain right = execute(node->getChild(1), ctxt);
                const std::string& pattern = getSymbolTable().resolve(left);
                const std::string& text = getSymbolTable().resolve(right);
                bool result = false;
                try {
                    result = std::regex_match(text, std::regex(pattern));
                } catch (...) {
                    std::cerr << "warning: wrong pattern provided for match(\"" << pattern << "\",\"" << text
                              << "\").\n";
                }
                return result;
            }
            case (BinaryConstraintOp::NOT_MATCH): {
                RamDomain left = execute(node->getChild(0), ctxt);
                RamDomain right = execute(node->getChild(1), ctxt);
                const std::string& pattern = getSymbolTable().resolve(left);
                const std::string& text = getSymbolTable().resolve(right);
                bool result = false;
                try {
                    result = !std::regex_match(text, std::regex(pattern));
                } catch (...) {
                    std::cerr << "warning: wrong pattern provided for !match(\"" << pattern << "\",\"" << text
                              << "\").\n";
                }
                return result;
            }
            case (BinaryConstraintOp::CONTAINS): {
                RamDomain left = execute(node->getChild(0), ctxt);
                RamDomain right = execute(node->getChild(1), ctxt);
                const std::string& pattern = getSymbolTable().resolve(left);
                const std::string& text = getSymbolTable().resolve(right);
                return text.find(pattern) != std::string::npos;
            }
            case (BinaryConstraintOp::NOT_CONTAINS): {
                RamDomain left = execute(node->getChild(0), ctxt);
                RamDomain right = execute(node->getChild(1), ctxt);
                const std::string& pattern = getSymbolTable().resolve(left);
                const std::string& text = getSymbolTable().resolve(right);
                return text.find(pattern) == std::string::npos;
            }
            default:
                assert(false && "unsupported operator");
                return false;
        }
        ESAC(Constraint)

        CASE(TupleOperation)
        bool result = execute(node->getChild(0), ctxt);

        if (profileEnabled && !cur->getProfileText().empty()) {
            auto& currentFrequencies = frequencies[cur->getProfileText()];
            while (currentFrequencies.size() <= getIterationNumber()) {
                currentFrequencies.emplace_back(0);
            }
            frequencies[cur->getProfileText()][getIterationNumber()]++;
        }
        return result;
        ESAC(TupleOperation)

        CASE(Scan)
        // get the targeted relation
        auto& rel = getRelation(node->getData(0));

        // use simple iterator
        for (const RamDomain* tuple : rel) {
            ctxt[cur->getTupleId()] = tuple;
            if (!execute(node->getChild(0), ctxt)) {
                break;
            }
        }
        return true;
        ESAC(Scan)

        CASE(ParallelScan)
        auto preamble = node->getPreamble();
        auto& rel = getRelation(node->getData(0));

        auto pStream = rel.partitionScan(numOfThreads);

        PARALLEL_START;
        InterpreterContext newCtxt(ctxt);
        auto viewInfo = preamble->getViewInfoForNested();
        for (const auto& info : viewInfo) {
            newCtxt.createView(*getRelationHandle(info[0]), info[1], info[2]);
        }
        pfor(auto it = pStream.begin(); it < pStream.end(); it++) {
            for (const TupleRef& val : *it) {
                newCtxt[cur->getTupleId()] = val.getBase();
                if (!execute(node->getChild(0), newCtxt)) {
                    break;
                }
            }
        }
        PARALLEL_END;
        return true;
        ESAC(ParallelScan)

        CASE(IndexScan)
        // create pattern tuple for range query
        size_t arity = cur->getRelation().getArity();
        RamDomain low[arity];
        RamDomain hig[arity];
        for (size_t i = 0; i < arity; i++) {
            if (node->getChild(i) != nullptr) {
                low[i] = execute(node->getChild(i), ctxt);
                hig[i] = low[i];
            } else {
                low[i] = MIN_RAM_DOMAIN;
                hig[i] = MAX_RAM_DOMAIN;
            }
        }

        size_t viewId = node->getData(0);
        auto& view = ctxt.getView(viewId);
        // conduct range query
        for (auto data : view->range(TupleRef(low, arity), TupleRef(hig, arity))) {
            ctxt[cur->getTupleId()] = &data[0];
            if (!execute(node->getChild(arity), ctxt)) {
                break;
            }
        }
        return true;
        ESAC(IndexScan)

        CASE(ParallelIndexScan)
        auto preamble = node->getPreamble();
        auto& rel = getRelation(node->getData(0));

        // create pattern tuple for range query
        size_t arity = rel.getArity();
        RamDomain low[arity];
        RamDomain hig[arity];
        for (size_t i = 0; i < arity; i++) {
            if (node->getChild(i)) {
                low[i] = execute(node->getChild(i), ctxt);
                hig[i] = low[i];
            } else {
                low[i] = MIN_RAM_DOMAIN;
                hig[i] = MAX_RAM_DOMAIN;
            }
        }

        size_t indexPos = node->getData(1);
        auto pStream = rel.partitionRange(indexPos, TupleRef(low, arity), TupleRef(hig, arity), numOfThreads);

        PARALLEL_START;
        InterpreterContext newCtxt(ctxt);
        auto viewInfo = preamble->getViewInfoForNested();
        for (const auto& info : viewInfo) {
            newCtxt.createView(*getRelationHandle(info[0]), info[1], info[2]);
        }
        pfor(auto it = pStream.begin(); it < pStream.end(); it++) {
            for (const TupleRef& val : *it) {
                newCtxt[cur->getTupleId()] = val.getBase();
                if (!execute(node->getChild(arity), newCtxt)) {
                    break;
                }
            }
        }
        PARALLEL_END;

        return true;
        ESAC(ParallelIndexScan)

        CASE(Choice)
        // get the targeted relation
        auto& rel = getRelation(node->getData(0));

        // use simple iterator
        for (const RamDomain* tuple : rel) {
            ctxt[cur->getTupleId()] = tuple;
            if (execute(node->getChild(0), ctxt)) {
                execute(node->getChild(1), ctxt);
                break;
            }
        }
        return true;
        ESAC(Choice)

        CASE(ParallelChoice)
        auto preamble = node->getPreamble();
        auto& rel = getRelation(node->getData(0));

        auto pStream = rel.partitionScan(numOfThreads);
        auto viewInfo = preamble->getViewInfoForNested();
        PARALLEL_START;
        InterpreterContext newCtxt(ctxt);
        for (const auto& info : viewInfo) {
            newCtxt.createView(*getRelationHandle(info[0]), info[1], info[2]);
        }
        pfor(auto it = pStream.begin(); it < pStream.end(); it++) {
            for (const TupleRef& val : *it) {
                newCtxt[cur->getTupleId()] = val.getBase();
                if (execute(node->getChild(0), newCtxt)) {
                    execute(node->getChild(1), newCtxt);
                    break;
                }
            }
        }
        PARALLEL_END;
        return true;
        ESAC(ParallelChoice)

        CASE(IndexChoice)
        // create pattern tuple for range query
        size_t arity = cur->getRelation().getArity();
        RamDomain low[arity];
        RamDomain hig[arity];
        for (size_t i = 0; i < arity; i++) {
            if (node->getChild(i) != nullptr) {
                low[i] = execute(node->getChild(i), ctxt);
                hig[i] = low[i];
            } else {
                low[i] = MIN_RAM_DOMAIN;
                hig[i] = MAX_RAM_DOMAIN;
            }
        }

        size_t viewId = node->getData(0);
        auto& view = ctxt.getView(viewId);

        for (auto ip : view->range(TupleRef(low, arity), TupleRef(hig, arity))) {
            const RamDomain* data = &ip[0];
            ctxt[cur->getTupleId()] = data;
            if (execute(node->getChild(arity), ctxt)) {
                execute(node->getChild(arity + 1), ctxt);
                break;
            }
        }
        return true;
        ESAC(IndexChoice)

        CASE(ParallelIndexChoice)
        auto preamble = node->getPreamble();
        auto& rel = getRelation(node->getData(0));

        auto viewInfo = preamble->getViewInfoForNested();

        // create pattern tuple for range query
        size_t arity = rel.getArity();
        RamDomain low[arity];
        RamDomain hig[arity];
        for (size_t i = 0; i < arity; i++) {
            if (node->getChild(i) != nullptr) {
                low[i] = execute(node->getChild(i), ctxt);
                hig[i] = low[i];
            } else {
                low[i] = MIN_RAM_DOMAIN;
                hig[i] = MAX_RAM_DOMAIN;
            }
        }

        size_t indexPos = node->getData(1);
        auto pStream = rel.partitionRange(indexPos, TupleRef(low, arity), TupleRef(hig, arity), numOfThreads);

        PARALLEL_START;
        InterpreterContext newCtxt(ctxt);
        for (const auto& info : viewInfo) {
            newCtxt.createView(*getRelationHandle(info[0]), info[1], info[2]);
        }
        pfor(auto it = pStream.begin(); it < pStream.end(); it++) {
            for (const TupleRef& val : *it) {
                newCtxt[cur->getTupleId()] = val.getBase();
                if (execute(node->getChild(arity), newCtxt)) {
                    execute(node->getChild(arity + 1), newCtxt);
                    break;
                }
            }
        }
        PARALLEL_END;

        return true;
        ESAC(ParallelIndexChoice)

        CASE(UnpackRecord)
        RamDomain ref = execute(node->getChild(0), ctxt);

        // check for null
        if (isNullInterpreter(ref)) {
            return true;
        }

        // update environment variable
        size_t arity = cur->getArity();
        const RamDomain* tuple = unpackInterpreter(ref, arity);

        // save reference to temporary value
        ctxt[cur->getTupleId()] = tuple;

        // run nested part - using base class visitor
        return execute(node->getChild(1), ctxt);
        ESAC(UnpackRecord)

        CASE(Aggregate)
        // get the targeted relation
        const InterpreterRelation& rel = getRelation(node->getData(0));

        // initialize result
        RamDomain res = 0;
        switch (cur->getFunction()) {
            case souffle::MIN:
                res = MAX_RAM_DOMAIN;
                break;
            case souffle::MAX:
                res = MIN_RAM_DOMAIN;
                break;
            case souffle::COUNT:
                res = 0;
                break;
            case souffle::SUM:
                res = 0;
                break;
        }

        for (const RamDomain* data : rel) {
            ctxt[cur->getTupleId()] = data;

            if (!execute(node->getChild(0), ctxt)) {
                continue;
            }

            // count is easy
            if (cur->getFunction() == souffle::COUNT) {
                ++res;
                continue;
            }

            // aggregation is a bit more difficult

            // eval target expression
            RamDomain val = execute(node->getChild(1), ctxt);

            switch (cur->getFunction()) {
                case souffle::MIN:
                    res = std::min(res, val);
                    break;
                case souffle::MAX:
                    res = std::max(res, val);
                    break;
                case souffle::COUNT:
                    res = 0;
                    break;
                case souffle::SUM:
                    res += val;
                    break;
            }
        }

        // write result to environment
        RamDomain tuple[1];
        tuple[0] = res;
        ctxt[cur->getTupleId()] = tuple;

        if (cur->getFunction() == souffle::MAX && res == MIN_RAM_DOMAIN) {
            // no maximum found
            return true;
        } else if (cur->getFunction() == souffle::MIN && res == MAX_RAM_DOMAIN) {
            // no minimum found
            return true;
        } else {
            // run nested part - using base class visitor
            return execute(node->getChild(2), ctxt);
        }
        ESAC(Aggregate)

        CASE(IndexAggregate)
        // initialize result
        RamDomain res = 0;
        switch (cur->getFunction()) {
            case souffle::MIN:
                res = MAX_RAM_DOMAIN;
                break;
            case souffle::MAX:
                res = MIN_RAM_DOMAIN;
                break;
            case souffle::COUNT:
                res = 0;
                break;
            case souffle::SUM:
                res = 0;
                break;
        }

        // init temporary tuple for this level
        size_t arity = cur->getRelation().getArity();

        // get lower and upper boundaries for iteration
        RamDomain low[arity];
        RamDomain hig[arity];

        for (size_t i = 0; i < arity; i++) {
            if (node->getChild(i) != nullptr) {
                low[i] = execute(node->getChild(i), ctxt);
                hig[i] = low[i];
            } else {
                low[i] = MIN_RAM_DOMAIN;
                hig[i] = MAX_RAM_DOMAIN;
            }
        }

        size_t viewId = node->getData(1);
        auto& view = ctxt.getView(viewId);

        for (auto ip : view->range(TupleRef(low, arity), TupleRef(hig, arity))) {
            // link tuple
            const RamDomain* data = &ip[0];
            ctxt[cur->getTupleId()] = data;

            if (!execute(node->getChild(arity), ctxt)) {
                continue;
            }

            // count is easy
            if (cur->getFunction() == souffle::COUNT) {
                ++res;
                continue;
            }

            // aggregation is a bit more difficult

            // eval target expression
            RamDomain val = execute(node->getChild(arity + 1), ctxt);

            switch (cur->getFunction()) {
                case souffle::MIN:
                    res = std::min(res, val);
                    break;
                case souffle::MAX:
                    res = std::max(res, val);
                    break;
                case souffle::COUNT:
                    res = 0;
                    break;
                case souffle::SUM:
                    res += val;
                    break;
            }
        }

        // write result to environment
        RamDomain tuple[1];
        tuple[0] = res;
        ctxt[cur->getTupleId()] = tuple;

        // run nested part - using base class visitor
        if (cur->getFunction() == souffle::MAX && res == MIN_RAM_DOMAIN) {
            // no maximum found
            return true;
        } else if (cur->getFunction() == souffle::MIN && res == MAX_RAM_DOMAIN) {
            // no minimum found
            return true;
        } else {
            // run nested part - using base class visitor
            return execute(node->getChild(arity + 2), ctxt);
        }
        ESAC(IndexAggregate)

        CASE_NO_CAST(Break)
        // check condition
        if (execute(node->getChild(0), ctxt)) {
            return false;
        }
        return execute(node->getChild(1), ctxt);
        ESAC(Break)

        CASE(Filter)
        bool result = true;
        // check condition
        if (execute(node->getChild(0), ctxt)) {
            // process nested
            result = execute(node->getChild(1), ctxt);
        }

        if (profileEnabled && !cur->getProfileText().empty()) {
            auto& currentFrequencies = frequencies[cur->getProfileText()];
            while (currentFrequencies.size() <= getIterationNumber()) {
                currentFrequencies.emplace_back(0);
            }
            frequencies[cur->getProfileText()][getIterationNumber()]++;
        }
        return result;
        ESAC(Filter)

        CASE(Project)
        size_t arity = cur->getRelation().getArity();
        RamDomain tuple[arity];
        for (size_t i = 0; i < arity; i++) {
            tuple[i] = execute(node->getChild(i), ctxt);
        }

        // insert in target relation
        InterpreterRelation& rel = getRelation(node->getData(0));
        rel.insert(tuple);
        return true;
        ESAC(Project)

        CASE(SubroutineReturnValue)
        for (size_t i = 0; i < cur->getValues().size(); ++i) {
            if (node->getChild(i) == nullptr) {
                ctxt.addReturnValue(0, true);
            } else {
                ctxt.addReturnValue(execute(node->getChild(i), ctxt));
            }
        }
        return true;
        ESAC(SubroutineReturnValue)

        CASE_NO_CAST(Sequence)
        for (const auto& child : node->getChildren()) {
            if (!execute(child.get(), ctxt)) {
                return false;
            }
        }
        return true;
        ESAC(Sequence)

        CASE_NO_CAST(Parallel)
        for (const auto& child : node->getChildren()) {
            if (!execute(child.get(), ctxt)) {
                return false;
            }
        }
        return true;
        ESAC(Parallel)

        CASE_NO_CAST(Loop)
        resetIterationNumber();
        while (execute(node->getChild(0), ctxt)) {
            incIterationNumber();
        }
        resetIterationNumber();
        return true;
        ESAC(Loop)

        CASE_NO_CAST(Exit)
        return !execute(node->getChild(0), ctxt);
        ESAC(Exit)

        CASE(LogRelationTimer)
        Logger logger(cur->getMessage().c_str(), getIterationNumber(),
                std::bind(&InterpreterRelation::size, &getRelation(node->getData(0))));
        return execute(node->getChild(0), ctxt);
        ESAC(LogRelationTimer)

        CASE(LogTimer)
        Logger logger(cur->getMessage().c_str(), getIterationNumber());
        return execute(node->getChild(0), ctxt);
        ESAC(LogTimer)

        CASE(DebugInfo)
        SignalHandler::instance()->setMsg(cur->getMessage().c_str());
        return execute(node->getChild(0), ctxt);
        ESAC(DebugInfo)

        CASE(Stratum)
        if (profileEnabled) {
            std::map<std::string, size_t> relNames;
            visitDepthFirst(*cur, [&](const RamCreate& create) {
                relNames[create.getRelation().getName()] = create.getRelation().getArity();
            });
            for (const auto& rel : relNames) {
                // Skip temporary relations, marked with '@'
                if (rel.first[0] == '@') {
                    continue;
                }
                ProfileEventSingleton::instance().makeStratumRecord(
                        cur->getIndex(), "relation", rel.first, "arity", std::to_string(rel.second));
            }
        }
        return execute(node->getChild(0), ctxt);
        ESAC(Stratum)

        CASE(Create)
        createRelation(cur->getRelation(), isa->getIndexes(cur->getRelation()), node->getData(0));
        return true;
        ESAC(Create)

        CASE_NO_CAST(Clear)
        getRelation(node->getData(0)).purge();
        return true;
        ESAC(Clear)

        CASE_NO_CAST(Drop)
        dropRelation(node->getData(0));
        return true;
        ESAC(Drop)

        CASE(LogSize)
        const InterpreterRelation& rel = getRelation(node->getData(0));
        ProfileEventSingleton::instance().makeQuantityEvent(
                cur->getMessage(), rel.size(), getIterationNumber());
        return true;
        ESAC(LogSize)

        CASE(Load)
        for (IODirectives ioDirectives : cur->getIODirectives()) {
            try {
                InterpreterRelation& relation = getRelation(node->getData(0));
                std::vector<bool> symbolMask;
                for (auto& cur : cur->getRelation().getAttributeTypeQualifiers()) {
                    symbolMask.push_back(cur[0] == 's');
                }
                IOSystem::getInstance()
                        .getReader(symbolMask, getSymbolTable(), ioDirectives,
                                Global::config().has("provenance"))
                        ->readAll(relation);
            } catch (std::exception& e) {
                std::cerr << "Error loading data: " << e.what() << "\n";
            }
        }
        return true;
        ESAC(Load)

        CASE(Store)
        for (IODirectives ioDirectives : cur->getIODirectives()) {
            try {
                std::vector<bool> symbolMask;
                for (auto& cur : cur->getRelation().getAttributeTypeQualifiers()) {
                    symbolMask.push_back(cur[0] == 's');
                }
                IOSystem::getInstance()
                        .getWriter(symbolMask, getSymbolTable(), ioDirectives,
                                Global::config().has("provenance"))
                        ->writeAll(getRelation(node->getData(0)));
            } catch (std::exception& e) {
                std::cerr << e.what();
                exit(1);
            }
        }
        return true;
        ESAC(Store)

        CASE(Fact)
        size_t arity = cur->getRelation().getArity();
        RamDomain tuple[arity];

        for (size_t i = 0; i < arity; ++i) {
            tuple[i] = execute(node->getChild(i), ctxt);
        }
        getRelation(node->getData(0)).insert(tuple);
        return true;
        ESAC(Fact)

        CASE_NO_CAST(Query)
        InterpreterPreamble* preamble = node->getPreamble();

        // Execute view-free operations in outer filter if any.
        auto& viewFreeOps = preamble->getOuterFilterViewFreeOps();
        for (auto& op : viewFreeOps) {
            if (!execute(op.get(), ctxt)) {
                return true;
            }
        }

        // Create Views for outer filter operation if any.
        auto& viewsForOuter = preamble->getViewInfoForFilter();
        for (auto& info : viewsForOuter) {
            ctxt.createView(*getRelationHandle(info[0]), info[1], info[2]);
        }

        // Execute outer filter operation.
        auto& viewOps = preamble->getOuterFilterViewOps();
        for (auto& op : viewOps) {
            if (!execute(op.get(), ctxt)) {
                return true;
            }
        }

        if (preamble->isParallel) {
            // If Parallel is true, holds views creation unitl parallel instructions.
        } else {
            // Issue views for nested operation.
            auto& viewsForNested = preamble->getViewInfoForNested();
            for (auto& info : viewsForNested) {
                ctxt.createView(*getRelationHandle(info[0]), info[1], info[2]);
            }
        }
        execute(node->getChild(0), ctxt);
        return true;
        ESAC(Query)

        CASE_NO_CAST(Merge)
        // get involved relation
        InterpreterRelation& src = getRelation(node->getData(0));
        InterpreterRelation& trg = getRelation(node->getData(1));

        if (dynamic_cast<InterpreterEqRelation*>(&trg) != nullptr) {
            // expand src with the new knowledge generated by insertion.
            src.extend(trg);
        }
        // merge in all elements
        trg.insert(src);

        // done
        return true;
        ESAC(Merge)

        CASE_NO_CAST(Swap)
        swapRelation(node->getData(0), node->getData(1));
        return true;
        ESAC(Swap)

        default:
            assert(false && "Unhandled\n");
    }
}

}  // namespace souffle
