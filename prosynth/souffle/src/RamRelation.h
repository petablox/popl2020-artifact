/*
 * Souffle - A Datalog Compiler
 * Copyright (c) 2013, 2014, Oracle and/or its affiliates. All rights reserved
 * Licensed under the Universal Permissive License v 1.0 as shown at:
 * - https://opensource.org/licenses/UPL
 * - <souffle root>/licenses/SOUFFLE-UPL.txt
 */

/************************************************************************
 *
 * @file RamRelation.h
 *
 * Defines the class for ram relations
 ***********************************************************************/

#pragma once

#include "IODirectives.h"
#include "ParallelUtils.h"
#include "RamNode.h"
#include "RamTypes.h"
#include "RelationRepresentation.h"
#include "SymbolTable.h"
#include "Table.h"
#include "Util.h"

#include <list>
#include <map>
#include <string>
#include <utility>
#include <vector>

namespace souffle {

/**
 * @class RamRelation
 * @brief A RAM Relation in the RAM intermediate representation.
 */
class RamRelation : public RamNode {
protected:
    /** Name of relation */
    const std::string name;

    /** Arity, i.e., number of attributes */
    const size_t arity;

    /** Name of attributes */
    const std::vector<std::string> attributeNames;

    /** Type of attributes */
    const std::vector<std::string> attributeTypeQualifiers;

    /** Data-structure representation */
    const RelationRepresentation representation;

public:
    /** Used by Interpreter only */
    mutable void* relation = nullptr;

    RamRelation(const std::string name, const size_t arity, const std::vector<std::string> attributeNames,
            const std::vector<std::string> attributeTypeQualifiers,
            const RelationRepresentation representation)
            : name(std::move(name)), arity(arity), attributeNames(std::move(attributeNames)),
              attributeTypeQualifiers(std::move(attributeTypeQualifiers)), representation(representation) {
        assert(this->attributeNames.size() == arity || this->attributeNames.empty());
        assert(this->attributeTypeQualifiers.size() == arity || this->attributeTypeQualifiers.empty());
    }

    /** @brief Get name */
    const std::string& getName() const {
        return name;
    }

    /** @brief Get argument */
    const std::string getArg(uint32_t i) const {
        if (!attributeNames.empty()) {
            return attributeNames[i];
        }
        if (arity == 0) {
            return "";
        }
        return "c" + std::to_string(i);
    }

    /** @brief Get Argument Type Qualifier */
    const std::string getArgTypeQualifier(uint32_t i) const {
        return (i < attributeTypeQualifiers.size()) ? attributeTypeQualifiers[i] : "";
    }

    const std::vector<std::string>& getAttributeTypeQualifiers() const {
        return attributeTypeQualifiers;
    }

    /** @brief Is nullary relation */
    const bool isNullary() const {
        return arity == 0;
    }

    /** @brief Relation representation type */
    const RelationRepresentation getRepresentation() const {
        return representation;
    }

    /** @brief Is temporary relation (for semi-naive evaluation) */
    const bool isTemp() const {
        return name.at(0) == '@';
    }

    /* @brief Get arity of relation */
    unsigned getArity() const {
        return arity;
    }

    /* @brief Compare two relations via their name */
    bool operator<(const RamRelation& other) const {
        return name < other.name;
    }

    void print(std::ostream& out) const override {
        out << name;
        if (arity > 0) {
            out << "(" << getArg(0) << ":" << attributeTypeQualifiers[0];
            for (unsigned i = 1; i < arity; i++) {
                out << ",";
                out << getArg(i) << ":" << attributeTypeQualifiers[i];
            }
            out << ")";
            out << " " << representation;
        } else {
            out << " nullary";
        }
    }

    RamRelation* clone() const override {
        return new RamRelation(name, arity, attributeNames, attributeTypeQualifiers, representation);
    }

protected:
    bool equal(const RamNode& node) const override {
        assert(nullptr != dynamic_cast<const RamRelation*>(&node));
        const auto& other = static_cast<const RamRelation&>(node);
        return name == other.name && arity == other.arity && attributeNames == other.attributeNames &&
               attributeTypeQualifiers == other.attributeTypeQualifiers &&
               representation == other.representation && isTemp() == other.isTemp();
    }
};

/**
 * @class RamRelationReference
 * @brief A RAM Relation in the RAM intermediate representation.
 */
class RamRelationReference : public RamNode {
public:
    RamRelationReference(const RamRelation* relation) : relation(relation) {
        assert(relation != nullptr && "null relation");
    }

    /** @brief Get reference */
    const RamRelation* get() const {
        assert(relation != nullptr && "relation reference is a null-pointer");
        return relation;
    }

    void print(std::ostream& out) const override {
        out << relation->getName();
    }

    RamRelationReference* clone() const override {
        return new RamRelationReference(relation);
    }

protected:
    /** Name of relation */
    const RamRelation* relation;

    bool equal(const RamNode& node) const override {
        assert(nullptr != dynamic_cast<const RamRelationReference*>(&node));
        const auto& other = static_cast<const RamRelationReference&>(node);
        return relation == other.relation;
    }
};

}  // end of namespace souffle
