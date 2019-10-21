/*
 * Souffle - A Datalog Compiler
 * Copyright (c) 2017, The Souffle Developers. All rights reserved
 * Licensed under the Universal Permissive License v 1.0 as shown at:
 * - https://opensource.org/licenses/UPL
 * - <souffle root>/licenses/SOUFFLE-UPL.txt
 */

/************************************************************************
 *
 * @file ExplainProvenance.h
 *
 * Abstract class for implementing an instance of the explain interface for provenance
 *
 ***********************************************************************/

#pragma once

#include "ExplainTree.h"
#include "RamTypes.h"
#include "SouffleInterface.h"
#include "WriteStreamCSV.h"

#include <sstream>
#include <string>
#include <vector>

namespace souffle {

/** utility function to split a string */
inline std::vector<std::string> split(const std::string& s, char delim, int times = -1) {
    std::vector<std::string> v;
    std::stringstream ss(s);
    std::string item;

    while ((times > 0 || times <= -1) && std::getline(ss, item, delim)) {
        v.push_back(item);
        times--;
    }

    if (ss.peek() != EOF) {
        std::string remainder;
        std::getline(ss, remainder);
        v.push_back(remainder);
    }

    return v;
}

class ExplainProvenance {
public:
    ExplainProvenance(SouffleProgram& prog) : prog(prog), symTable(prog.getSymbolTable()) {}
    virtual ~ExplainProvenance() = default;

    virtual void setup() = 0;

    virtual std::unique_ptr<TreeNode> explain(
            std::string relName, std::vector<std::string> tuple, size_t depthLimit) = 0;

    virtual std::unique_ptr<TreeNode> explainSubproof(
            std::string relName, RamDomain label, size_t depthLimit) = 0;

    virtual std::vector<std::string> explainNegationGetVariables(
            std::string relName, std::vector<std::string> args, size_t ruleNum) = 0;

    virtual std::unique_ptr<TreeNode> explainNegation(std::string relName, size_t ruleNum,
            const std::vector<std::string>& tuple, std::map<std::string, std::string>& bodyVariables) = 0;

    virtual std::string getRule(std::string relName, size_t ruleNum) = 0;

    virtual std::vector<std::string> getRules(std::string relName) = 0;

    virtual std::string measureRelation(std::string relName) = 0;

    virtual void printRulesJSON(std::ostream& os) = 0;

    virtual std::string getRelationOutput(const std::string& relName) {
        auto rel = prog.getRelation(relName);
        if (rel == nullptr) {
            return "Relation " + relName + " not found\n";
        }

        // create symbol mask
        std::vector<bool> symMask(rel->getArity());

        for (size_t i = 0; i < rel->getArity(); i++) {
            if (*(rel->getAttrType(i)) == 's') {
                symMask.at(i) = true;
            }
        }

        // create IODirectives
        IODirectives dir;
        dir.setRelationName(relName);

        // redirect cout to stringstream
        std::stringstream out;
        auto originalCoutBuf = std::cout.rdbuf(out.rdbuf());

        // print relation
        printRelationOutput(symMask, dir, *rel);

        // restore original cout buffer
        std::cout.rdbuf(originalCoutBuf);

        return out.str();
    }

protected:
    SouffleProgram& prog;
    SymbolTable& symTable;

    std::vector<RamDomain> argsToNums(
            const std::string& relName, const std::vector<std::string>& args) const {
        std::vector<RamDomain> nums;

        auto rel = prog.getRelation(relName);
        if (rel == nullptr) {
            return nums;
        }

        for (size_t i = 0; i < args.size(); i++) {
            if (*rel->getAttrType(i) == 's') {
                // remove quotation marks
                if (args[i].size() >= 2 && args[i][0] == '"' && args[i][args[i].size() - 1] == '"') {
                    auto originalStr = args[i].substr(1, args[i].size() - 2);
                    nums.push_back(symTable.lookup(originalStr));
                }
            } else {
                nums.push_back(std::stoi(args[i]));
            }
        }

        return nums;
    }

    std::vector<std::string> numsToArgs(const std::string& relName, const std::vector<RamDomain>& nums,
            std::vector<bool>* err = nullptr) const {
        std::vector<std::string> args;

        auto rel = prog.getRelation(relName);
        if (rel == nullptr) {
            return args;
        }

        for (size_t i = 0; i < nums.size(); i++) {
            if (err && (*err)[i]) {
                args.push_back("_");
            } else {
                if (*rel->getAttrType(i) == 's') {
                    args.push_back("\"" + std::string(symTable.resolve(nums[i])) + "\"");
                } else {
                    args.push_back(std::to_string(nums[i]));
                }
            }
        }

        return args;
    }

    virtual void printRelationOutput(
            const std::vector<bool>& symMask, const IODirectives& ioDir, const Relation& rel) = 0;
};

}  // end of namespace souffle
