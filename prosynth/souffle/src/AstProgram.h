/*
 * Souffle - A Datalog Compiler
 * Copyright (c) 2013, Oracle and/or its affiliates. All rights reserved
 * Licensed under the Universal Permissive License v 1.0 as shown at:
 * - https://opensource.org/licenses/UPL
 * - <souffle root>/licenses/SOUFFLE-UPL.txt
 */

/************************************************************************
 *
 * @file AstProgram.h
 *
 * Define a class that represents a Datalog program consisting of types,
 * relations, and clauses.
 *
 ***********************************************************************/

#pragma once

#include "AstComponent.h"
#include "AstFunctorDeclaration.h"
#include "AstIO.h"
#include "AstNode.h"
#include "AstPragma.h"
#include "AstRelation.h"
#include "AstRelationIdentifier.h"
#include "AstType.h"
#include "Util.h"
#include <cassert>
#include <cstddef>
#include <iosfwd>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace souffle {

class AstClause;
class AstLoad;
class AstPrintSize;
class AstStore;
class AstRelation;

/**
 *  Intermediate representation of a datalog program
 *          that consists of relations, clauses and types
 */
class AstProgram : public AstNode {
public:
    /** Deleted copy constructor since instances can not be copied */
    AstProgram(const AstProgram&) = delete;

    /** A move constructor */
    AstProgram(AstProgram&& other) noexcept;

    /** A programs destructor */
    ~AstProgram() override = default;

    // -- Types ----------------------------------------------------------------

    /** Obtains the type with the given name */
    const AstType* getType(const AstTypeIdentifier& name) const;

    /** Gets a list of all types in this program */
    std::vector<const AstType*> getTypes() const;

    // -- Relations ------------------------------------------------------------

    /** Find and return the relation in the program given its name */
    AstRelation* getRelation(const AstRelationIdentifier& name) const;

    /** Get functor declaration */
    AstFunctorDeclaration* getFunctorDeclaration(const std::string& name) const;

    /** Get all relations in the program */
    std::vector<AstRelation*> getRelations() const;

    /** Get all io directives in the program */
    const std::vector<std::unique_ptr<AstLoad>>& getLoads() const;
    const std::vector<std::unique_ptr<AstPrintSize>>& getPrintSizes() const;
    const std::vector<std::unique_ptr<AstStore>>& getStores() const;

    /** Get all pragma directives in the program */
    const std::vector<std::unique_ptr<AstPragma>>& getPragmaDirectives() const;

    /** Return the number of relations in the program */
    size_t relationSize() const {
        return relations.size();
    }

    /** appends a new relation to this program -- after parsing */
    void appendRelation(std::unique_ptr<AstRelation> r);

    /** Remove a relation from the program. */
    void removeRelation(const AstRelationIdentifier& name);

    /** append a new clause to this program -- after parsing */
    void appendClause(std::unique_ptr<AstClause> clause);

    /** Removes a clause from this program */
    void removeClause(const AstClause* clause);

    /**
     * Obtains a list of clauses not associated to any relations. In
     * a valid program this list is always empty
     */
    std::vector<AstClause*> getOrphanClauses() const {
        return toPtrVector(clauses);
    }

    // -- Components -----------------------------------------------------------

    /** Obtains a list of all comprised components */
    std::vector<AstComponent*> getComponents() const {
        return toPtrVector(components);
    }

    /** Obtains a list of all component instantiations */
    std::vector<AstComponentInit*> getComponentInstantiations() const {
        return toPtrVector(instantiations);
    }

    // -- I/O ------------------------------------------------------------------

    /** Output the program to a given output stream */
    void print(std::ostream& os) const override;

    // -- Manipulation ---------------------------------------------------------

    /** Creates a clone of this AST sub-structure */
    AstProgram* clone() const override;

    /** Mutates this node */
    void apply(const AstNodeMapper& map) override;

    /** Obtains a list of all embedded child nodes */
    std::vector<const AstNode*> getChildNodes() const override {
        std::vector<const AstNode*> res;
        for (const auto& cur : types) {
            res.push_back(cur.second.get());
        }
        for (const auto& cur : relations) {
            res.push_back(cur.second.get());
        }
        for (const auto& cur : components) {
            res.push_back(cur.get());
        }
        for (const auto& cur : instantiations) {
            res.push_back(cur.get());
        }
        for (const auto& cur : clauses) {
            res.push_back(cur.get());
        }
        for (const auto& cur : pragmaDirectives) {
            res.push_back(cur.get());
        }
        for (const auto& cur : loads) {
            res.push_back(cur.get());
        }
        for (const auto& cur : printSizes) {
            res.push_back(cur.get());
        }
        for (const auto& cur : stores) {
            res.push_back(cur.get());
        }
        return res;
    }

protected:
    /** Implements the node comparison for this node type */
    bool equal(const AstNode& node) const override {
        assert(nullptr != dynamic_cast<const AstProgram*>(&node));
        const auto& other = static_cast<const AstProgram&>(node);

        // check list sizes
        if (types.size() != other.types.size()) {
            return false;
        }
        if (relations.size() != other.relations.size()) {
            return false;
        }

        // check types
        for (const auto& cur : types) {
            auto pos = other.types.find(cur.first);
            if (pos == other.types.end()) {
                return false;
            }
            if (*cur.second != *pos->second) {
                return false;
            }
        }

        // check relations
        for (const auto& cur : relations) {
            auto pos = other.relations.find(cur.first);
            if (pos == other.relations.end()) {
                return false;
            }
            if (*cur.second != *pos->second) {
                return false;
            }
        }

        // check components
        if (!equal_targets(components, other.components)) {
            return false;
        }
        if (!equal_targets(instantiations, other.instantiations)) {
            return false;
        }
        if (!equal_targets(clauses, other.clauses)) {
            return false;
        }
        if (!equal_targets(loads, other.loads)) {
            return false;
        }
        if (!equal_targets(printSizes, other.printSizes)) {
            return false;
        }
        if (!equal_targets(stores, other.stores)) {
            return false;
        }

        // no different found => programs are equal
        return true;
    }

private:
    friend class ComponentInstantiationTransformer;
    friend class ParserDriver;
    friend class ProvenanceTransformer;

    /** Program types  */
    std::map<AstTypeIdentifier, std::unique_ptr<AstType>> types;

    /** Program relations */
    std::map<AstRelationIdentifier, std::unique_ptr<AstRelation>> relations;

    /** External Functors */
    std::map<std::string, std::unique_ptr<AstFunctorDeclaration>> functors;

    /** The list of clauses provided by the user */
    std::vector<std::unique_ptr<AstClause>> clauses;

    /** The list of IO directives provided by the user */
    std::vector<std::unique_ptr<AstLoad>> loads;
    std::vector<std::unique_ptr<AstPrintSize>> printSizes;
    std::vector<std::unique_ptr<AstStore>> stores;

    /** Program components */
    std::vector<std::unique_ptr<AstComponent>> components;

    /** Component instantiations */
    std::vector<std::unique_ptr<AstComponentInit>> instantiations;

    /** Pragmas */
    std::vector<std::unique_ptr<AstPragma>> pragmaDirectives;

    /** a private constructor to restrict creation */
    AstProgram() = default;

    // -- Types ----------------------------------------------------------------

    /** Add the given type to the program. Asserts if a type with the
      same name has already been added.  */
    void addType(std::unique_ptr<AstType> type);

    // -- Relations ------------------------------------------------------------

    /** Add the given relation to the program. Asserts if a relation with the
     * same name has already been added. */
    void addRelation(std::unique_ptr<AstRelation> r);

    /** Add a clause to the program */
    void addClause(std::unique_ptr<AstClause> clause);

    /** Add an IO directive to the program */
    void addLoad(std::unique_ptr<AstLoad> directive);
    void addPrintSize(std::unique_ptr<AstPrintSize> directive);
    void addStore(std::unique_ptr<AstStore> directive);

    /** Add a pragma to the program */
    void addPragma(std::unique_ptr<AstPragma> r);

    /** Add a functor to the program */
    void addFunctorDeclaration(std::unique_ptr<souffle::AstFunctorDeclaration> f);

    // -- Components -----------------------------------------------------------

    /** Adds the given component to this program */
    void addComponent(std::unique_ptr<AstComponent> c) {
        components.push_back(std::move(c));
    }

    /** Adds a component instantiation */
    void addInstantiation(std::unique_ptr<AstComponentInit> i) {
        instantiations.push_back(std::move(i));
    }

    void finishParsing();
};

}  // end of namespace souffle
