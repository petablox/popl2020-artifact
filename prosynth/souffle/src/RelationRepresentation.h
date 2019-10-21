/*
 * Souffle - A Datalog Compiler
 * Copyright (c) 2019, The Souffle Developers. All rights reserved
 * Licensed under the Universal Permissive License v 1.0 as shown at:
 * - https://opensource.org/licenses/UPL
 * - <souffle root>/licenses/SOUFFLE-UPL.txt
 */

/************************************************************************
 *
 * @file RelationRepresentation.h
 *
 * Identifies the available data structures.
 ***********************************************************************/

#pragma once

#include <ostream>

namespace souffle {

/**
 * Available representations used for a relation.
 */
enum class RelationRepresentation {
    DEFAULT,
    // btree data-structure
    BTREE,
    // btree data-structure
    BRIE,
    // equivalence relation
    EQREL
};

inline std::ostream& operator<<(std::ostream& os, RelationRepresentation structure) {
    switch (structure) {
        case RelationRepresentation::BTREE:
            os << "btree";
            break;
        case RelationRepresentation::BRIE:
            os << "brie";
            break;
        case RelationRepresentation::EQREL:
            os << "eqrel";
            break;
        case RelationRepresentation::DEFAULT:
        default:
            break;
    }

    return os;
}

}  // end of namespace souffle
