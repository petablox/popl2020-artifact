/*
 * Souffle - A Datalog Compiler
 * Copyright (c) 2017, The Souffle Developers. All rights reserved
 * Licensed under the Universal Permissive License v 1.0 as shown at:
 * - https://opensource.org/licenses/UPL
 * - <souffle root>/licenses/SOUFFLE-UPL.txt
 */

/************************************************************************
 *
 * @file RamProgram.h
 *
 * Defines a Program of a relational algebra query
 *
 ***********************************************************************/

#pragma once

#include "RamStatement.h"
#include <memory>

namespace souffle {

/**
 * @class RamProgram
 * @brief RAM program relation declaration and functions
 *
 * A typical example:
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * PROGRAM
 *   DECLARATION
 *     A(x:i:number)
 *   END DECLARATION
 *   BEGIN MAIN
 *     ...
 *   END MAIN
 * END PROGRAM
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
class RamProgram : public RamNode {
public:
    RamProgram() = default;
    RamProgram(std::unique_ptr<RamStatement> main) : main(std::move(main)) {}

    std::vector<const RamNode*> getChildNodes() const override {
        std::vector<const RamNode*> children;
        children = main->getChildNodes();
        for (auto& r : relations) {
            children.push_back(r.second.get());
        }
        for (auto& s : subroutines) {
            children.push_back(s.second.get());
        }
        return children;
    }

    void print(std::ostream& out) const override {
        out << "PROGRAM" << std::endl;
        out << " DECLARATION" << std::endl;
        for (const auto& rel : relations) {
            out << "  ";
            rel.second->print(out);
            out << std::endl;
        }
        out << " END DECLARATION" << std::endl;
        for (const auto& subroutine : subroutines) {
            out << " SUBROUTINE " << subroutine.first << std::endl;
            subroutine.second->print(out, 2);
            out << " END SUBROUTINE" << std::endl;
        }
        out << " BEGIN MAIN" << std::endl;
        main->print(out, 2);
        out << " END MAIN" << std::endl;
        out << "END PROGRAM" << std::endl;
    }

    /** @brief Set a statement to main */
    void setMain(std::unique_ptr<RamStatement> stmt) {
        main = std::move(stmt);
    }

    /** @brief Get main program */
    RamStatement* getMain() const {
        assert(main && "Program has no main routine");
        return main.get();
    }

    /** @brief Add relation */
    void addRelation(std::unique_ptr<RamRelation> rel) {
        relations.insert(std::make_pair(rel->getName(), std::move(rel)));
    }

    /** @brief Get relation */
    const RamRelation* getRelation(const std::string& name) const {
        auto it = relations.find(name);
        if (it != relations.end()) {
            return it->second.get();
        } else {
            return nullptr;
        }
    }

    /** @brief Get relations map */
    const std::map<std::string, std::unique_ptr<RamRelation>>& getAllRelations() const {
        return this->relations;
    }

    /** @brief Add subroutine */
    void addSubroutine(std::string name, std::unique_ptr<RamStatement> subroutine) {
        subroutines.insert(std::make_pair(name, std::move(subroutine)));
    }

    /** @brief Get subroutines */
    const std::map<std::string, RamStatement*> getSubroutines() const {
        std::map<std::string, RamStatement*> subroutineRefs;
        for (auto& s : subroutines) {
            subroutineRefs.insert({s.first, s.second.get()});
        }
        return subroutineRefs;
    }

    /** @brief Get subroutine */
    const RamStatement& getSubroutine(const std::string& name) const {
        return *subroutines.at(name);
    }

    RamProgram* clone() const override {
        std::map<const RamRelation*, const RamRelation*> refMap;
        auto* res = new RamProgram(std::unique_ptr<RamStatement>(main->clone()));
        for (auto& cur : relations) {
            RamRelation* newRel = cur.second->clone();
            refMap[cur.second.get()] = newRel;
            res->addRelation(std::unique_ptr<RamRelation>(newRel));
        }
        for (auto& cur : subroutines) {
            res->addSubroutine(cur.first, std::unique_ptr<RamStatement>(cur.second->clone()));
        }
        res->apply(makeLambdaRamMapper([&](std::unique_ptr<RamNode> node) -> std::unique_ptr<RamNode> {
            // check whether it is a unnamed variable
            if (const RamRelationReference* relRef = dynamic_cast<RamRelationReference*>(node.get())) {
                const RamRelation* rel = refMap[relRef->get()];
                assert(rel != nullptr && "dangling RAM relation reference");
                return std::make_unique<RamRelationReference>(rel);
            } else {
                return node;
            }
        }));
        return res;
    }

    void apply(const RamNodeMapper& map) override {
        main = map(std::move(main));
        for (auto& cur : relations) {
            cur.second = map(std::move(cur.second));
        }
        for (auto& cur : subroutines) {
            cur.second = map(std::move(cur.second));
        }
    }

protected:
    /** Relations of RAM program */
    std::map<std::string, std::unique_ptr<RamRelation>> relations;

    /** Main program */
    std::unique_ptr<RamStatement> main;

    /** Subroutines for querying computed relations */
    std::map<std::string, std::unique_ptr<RamStatement>> subroutines;

    bool equal(const RamNode& node) const override {
        assert(nullptr != dynamic_cast<const RamProgram*>(&node));
        const auto& other = static_cast<const RamProgram&>(node);
        if (relations.size() != other.relations.size() || subroutines.size() != other.subroutines.size()) {
            return false;
        }
        for (auto& cur : subroutines) {
            if (other.getSubroutine(cur.first) != getSubroutine(cur.first)) {
                return false;
            }
        }
        for (auto& cur : relations) {
            if (other.getRelation(cur.first) != getRelation(cur.first)) {
                return false;
            }
        }
        return getMain() == other.getMain();
    }
};

}  // end of namespace souffle
