/*
 * Souffle - A Datalog Compiler
 * Copyright (c) 2013, Oracle and/or its affiliates. All rights reserved
 * Licensed under the Universal Permissive License v 1.0 as shown at:
 * - https://opensource.org/licenses/UPL
 * - <souffle root>/licenses/SOUFFLE-UPL.txt
 */

/************************************************************************
 *
 * @file AstClause.cpp
 *
 * Implements methods of class Clause that represents rules including facts,
 * predicates, and queries in a Datalog program.
 *
 ***********************************************************************/

#include "AstClause.h"
#include "AstLiteral.h"
#include "AstVisitor.h"
#include <algorithm>

namespace souffle {

class AstAggregator;

/*
 * Clause
 */

/* Add literal to body */
void AstClause::addToBody(std::unique_ptr<AstLiteral> l) {
    if (dynamic_cast<AstAtom*>(l.get())) {
        atoms.emplace_back(static_cast<AstAtom*>(l.release()));
    } else if (dynamic_cast<AstNegation*>(l.get())) {
        negations.emplace_back(static_cast<AstNegation*>(l.release()));
    } else if (dynamic_cast<AstProvenanceNegation*>(l.get())) {
        provNegations.emplace_back(static_cast<AstProvenanceNegation*>(l.release()));
    } else if (dynamic_cast<AstConstraint*>(l.get())) {
        constraints.emplace_back(static_cast<AstConstraint*>(l.release()));
    } else {
        assert(false && "Unsupported literal type!");
    }
}

/* Set the head of clause to h */
void AstClause::setHead(std::unique_ptr<AstAtom> h) {
    assert(!head && "Head is already set");
    head = std::move(h);
}

AstLiteral* AstClause::getBodyLiteral(size_t idx) const {
    if (idx < atoms.size()) {
        return atoms[idx].get();
    }
    idx -= atoms.size();
    if (idx < negations.size()) {
        return negations[idx].get();
    }
    idx -= negations.size();
    if (idx < provNegations.size()) {
        return provNegations[idx].get();
    }
    idx -= provNegations.size();
    return constraints[idx].get();
}

std::vector<AstLiteral*> AstClause::getBodyLiterals() const {
    std::vector<AstLiteral*> res;
    for (auto& cur : atoms) {
        res.push_back(cur.get());
    }
    for (auto& cur : negations) {
        res.push_back(cur.get());
    }
    for (auto& cur : provNegations) {
        res.push_back(cur.get());
    }
    for (auto& cur : constraints) {
        res.push_back(cur.get());
    }
    return res;
}

bool AstClause::isFact() const {
    // there must be a head
    if (head == nullptr) {
        return false;
    }
    // there must not be any body clauses
    if (getBodySize() != 0) {
        return false;
    }
    // and there are no aggregates
    bool hasAggregates = false;
    visitDepthFirst(*head, [&](const AstAggregator& cur) { hasAggregates = true; });
    return !hasAggregates;
}

void AstClause::print(std::ostream& os) const {
    if (head != nullptr) {
        head->print(os);
    }
    if (getBodySize() > 0) {
        os << " :- \n   ";
        os << join(getBodyLiterals(), ",\n   ", print_deref<AstLiteral*>());
    }
    os << ".";
    if (getExecutionPlan()) {
        getExecutionPlan()->print(os);
    }
}

void AstClause::reorderAtoms(const std::vector<unsigned int>& newOrder) {
    // Validate given order
    assert(newOrder.size() == atoms.size());
    std::vector<unsigned int> nopOrder;
    for (unsigned int i = 0; i < atoms.size(); i++) {
        nopOrder.push_back(i);
    }
    assert(std::is_permutation(nopOrder.begin(), nopOrder.end(), newOrder.begin()));

    // Reorder atoms
    std::vector<std::unique_ptr<AstAtom>> oldAtoms(atoms.size());
    atoms.swap(oldAtoms);
    for (unsigned int i = 0; i < newOrder.size(); i++) {
        atoms[i].swap(oldAtoms[newOrder[i]]);
    }
}

}  // end of namespace souffle
