/*
 * Souffle - A Datalog Compiler
 * Copyright (c) 2013, Oracle and/or its affiliates. All rights reserved
 * Licensed under the Universal Permissive License v 1.0 as shown at:
 * - https://opensource.org/licenses/UPL
 * - <souffle root>/licenses/SOUFFLE-UPL.txt
 */

/************************************************************************
 *
 * @file AstRelation.h
 *
 * Defines class Relation that represents relations in a Datalog program.
 * A relation can either be an IDB or EDB relation.
 *
 ***********************************************************************/

#pragma once

#include "AstAttribute.h"
#include "AstClause.h"
#include "AstIO.h"
#include "AstNode.h"
#include "AstRelationIdentifier.h"
#include "AstType.h"
#include "RelationRepresentation.h"

#include <iostream>
#include <memory>
#include <set>
#include <string>
#include <vector>

#include <cctype>

/** Types of relation qualifiers defined as bits in a word */

/* relation is read from csv file */
#define INPUT_RELATION (0x1)

/* relation is written to csv file */
#define OUTPUT_RELATION (0x2)

/* number of tuples are written to stdout */
#define PRINTSIZE_RELATION (0x4)

/* Rules of a relation defined in a component can be overwritten by sub-component */
#define OVERRIDABLE_RELATION (0x8)

/* Relation is inlined */
#define INLINE_RELATION (0x20)

/* Relation uses a brie data structure */
#define BRIE_RELATION (0x40)

/* Relation uses a btree data structure */
#define BTREE_RELATION (0x80)

/* Relation uses a union relation */
#define EQREL_RELATION (0x100)

/* Relation warnings are suppressed */
#define SUPPRESSED_RELATION (0x800)

namespace souffle {

/*!
 * @class Relation
 * @brief Intermediate representation of a datalog relation
 *
 * A relation has a name, types of its arguments, qualifier type,
 * and dependencies to other relations.
 *
 */
class AstRelation : public AstNode {
public:
    AstRelation() = default;

    ~AstRelation() override = default;

    /** Return the name of the relation */
    const AstRelationIdentifier& getName() const {
        return name;
    }

    /** Set name for this relation */
    void setName(const AstRelationIdentifier& n) {
        name = n;
    }

    /** Add a new used type to this relation */
    void addAttribute(std::unique_ptr<AstAttribute> attr) {
        assert(attr && "Undefined attribute");
        attributes.push_back(std::move(attr));
    }

    /** Return the arity of this relation */
    size_t getArity() const {
        return attributes.size();
    }

    /** Return the declared type at position @p idx */
    AstAttribute* getAttribute(size_t idx) const {
        return attributes[idx].get();
    }

    /** Obtains a list of the contained attributes */
    std::vector<AstAttribute*> getAttributes() const {
        return toPtrVector(attributes);
    }

    /** Return qualifier associated with this relation */
    int getQualifier() const {
        return qualifier;
    }

    /** Set qualifier associated with this relation */
    void setQualifier(int q) {
        qualifier = q;
        if (q & EQREL_RELATION) {
            representation = RelationRepresentation::EQREL;
        } else if (q & BRIE_RELATION) {
            representation = RelationRepresentation::BRIE;
        } else if (q & BTREE_RELATION) {
            representation = RelationRepresentation::BTREE;
        }

        if (q & INPUT_RELATION) {
            loads.emplace_back(new AstLoad());
            loads.back()->setName(getName());
            loads.back()->setSrcLoc(getSrcLoc());
        }
        if (q & OUTPUT_RELATION) {
            stores.emplace_back(new AstStore());
            stores.back()->setName(getName());
            stores.back()->setSrcLoc(getSrcLoc());
        }
        if (q & PRINTSIZE_RELATION) {
            stores.emplace_back(new AstPrintSize());
            stores.back()->setName(getName());
            stores.back()->setSrcLoc(getSrcLoc());
        }
    }

    /** Get representation for this relation */
    RelationRepresentation getRepresentation() const {
        return representation;
    }

    void setRepresentation(RelationRepresentation representation) {
        this->representation = representation;
    }

    /** Check whether relation is an overridable relation */
    bool isOverridable() const {
        return (qualifier & OVERRIDABLE_RELATION) != 0;
    }

    /** Check whether relation warnings are suppressed */
    bool isSuppressed() const {
        return (qualifier & SUPPRESSED_RELATION) != 0;
    }

    /** Check whether relation is an inlined relation */
    bool isInline() const {
        return (qualifier & INLINE_RELATION) != 0;
    }

    /** Check whether relation has a record in its head */
    bool hasRecordInHead() const {
        for (auto& cur : clauses) {
            for (auto* arg : cur->getHead()->getArguments()) {
                if (dynamic_cast<AstRecordInit*>(arg)) {
                    return true;
                }
            };
        }
        return false;
    }

    /** Operator overload, calls print if reference is given */
    friend std::ostream& operator<<(std::ostream& os, const AstRelation& rel) {
        rel.print(os);
        return os;
    }

    /** Operator overload, prints name if pointer is given */
    friend std::ostream& operator<<(std::ostream& os, const AstRelation* rel) {
        os << rel->getName();
        return os;
    }

    /** Print string representation of the relation to a given output stream */
    void print(std::ostream& os) const override {
        os << ".decl " << this->getName() << "(";
        if (!attributes.empty()) {
            os << attributes[0]->getAttributeName() << ":" << attributes[0]->getTypeName();

            for (size_t i = 1; i < attributes.size(); ++i) {
                os << "," << attributes[i]->getAttributeName() << ":" << attributes[i]->getTypeName();
            }
        }
        os << ") ";
        if (isOverridable()) {
            os << "overridable ";
        }
        if (isInline()) {
            os << "inline ";
        }
        os << representation << " ";
    }

    /** Creates a clone of this AST sub-structure */
    AstRelation* clone() const override {
        auto res = new AstRelation();
        res->name = name;
        res->setSrcLoc(getSrcLoc());
        for (const auto& cur : attributes) {
            res->attributes.emplace_back(cur->clone());
        }
        for (const auto& cur : clauses) {
            res->clauses.emplace_back(cur->clone());
        }
        for (const auto& cur : stores) {
            res->stores.emplace_back(cur->clone());
        }
        for (const auto& cur : loads) {
            res->loads.emplace_back(cur->clone());
        }
        res->qualifier = qualifier;
        return res;
    }

    /** Mutates this node */
    void apply(const AstNodeMapper& map) override {
        for (auto& cur : attributes) {
            cur = map(std::move(cur));
        }
        for (auto& cur : clauses) {
            cur = map(std::move(cur));
        }
        for (auto& cur : stores) {
            cur = map(std::move(cur));
        }
        for (auto& cur : loads) {
            cur = map(std::move(cur));
        }
    }

    /** Return i-th clause associated with this relation */
    AstClause* getClause(size_t idx) const {
        return clauses[idx].get();
    }

    /** Obtains a list of the associated clauses */
    std::vector<AstClause*> getClauses() const {
        return toPtrVector(clauses);
    }

    /** Add a clause to the relation */
    void addClause(std::unique_ptr<AstClause> clause) {
        assert(clause && "Undefined clause");
        assert(clause->getHead() && "Undefined head of the clause");
        assert(clause->getHead()->getName() == name &&
                "Name of the atom in the head of the clause and the relation do not match");
        clauses.push_back(std::move(clause));
    }

    /** Removes the given clause from this relation */
    bool removeClause(const AstClause* clause) {
        for (auto it = clauses.begin(); it != clauses.end(); ++it) {
            if (**it == *clause) {
                clauses.erase(it);
                return true;
            }
        }
        return false;
    }

    /** Return the number of clauses associated with this relation */
    size_t clauseSize() const {
        return clauses.size();
    }

    /** Obtains a list of all embedded child nodes */
    std::vector<const AstNode*> getChildNodes() const override {
        std::vector<const AstNode*> res;
        for (const auto& cur : attributes) {
            res.push_back(cur.get());
        }
        for (const auto& cur : clauses) {
            res.push_back(cur.get());
        }
        for (const auto& cur : stores) {
            res.push_back(cur.get());
        }
        for (const auto& cur : loads) {
            res.push_back(cur.get());
        }
        return res;
    }

    void addStore(std::unique_ptr<AstStore> directive) {
        assert(directive && "Undefined directive");
        stores.push_back(std::move(directive));
    }

    void addLoad(std::unique_ptr<AstLoad> directive) {
        assert(directive && "Undefined directive");
        loads.push_back(std::move(directive));
    }

    std::vector<AstStore*> getStores() const {
        return toPtrVector(stores);
    }
    std::vector<AstLoad*> getLoads() const {
        return toPtrVector(loads);
    }

protected:
    /** Name of relation */
    AstRelationIdentifier name;

    /** Attributes of the relation */
    std::vector<std::unique_ptr<AstAttribute>> attributes;

    /** Qualifier of relation (i.e., output or not an output relation) */
    // TODO: Change to a set of qualifiers
    int qualifier = 0;

    /** Clauses associated with this relation. Clauses could be
     * either facts or rules.
     */
    std::vector<std::unique_ptr<AstClause>> clauses;

    /** IO directives associated with this relation. */
    std::vector<std::unique_ptr<AstStore>> stores;
    std::vector<std::unique_ptr<AstLoad>> loads;

    /** Datastructure to use for this relation */
    RelationRepresentation representation{RelationRepresentation::DEFAULT};

    /** Implements the node comparison for this node type */
    bool equal(const AstNode& node) const override {
        assert(nullptr != dynamic_cast<const AstRelation*>(&node));
        const auto& other = static_cast<const AstRelation&>(node);
        return name == other.name && equal_targets(attributes, other.attributes) &&
               equal_targets(clauses, other.clauses);
    }
};

struct AstNameComparison {
    bool operator()(const AstRelation* x, const AstRelation* y) const {
        if (x != nullptr && y != nullptr) {
            return x->getName() < y->getName();
        }
        return y != nullptr;
    }
};

using AstRelationSet = std::set<const AstRelation*, AstNameComparison>;

}  // end of namespace souffle
