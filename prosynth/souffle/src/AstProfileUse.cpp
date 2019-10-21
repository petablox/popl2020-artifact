/*
 * Souffle - A Datalog Compiler
 * Copyright (c) 2018, The Souffle Developers. All rights reserved
 * Licensed under the Universal Permissive License v 1.0 as shown at:
 * - https://opensource.org/licenses/UPL
 * - <souffle root>/licenses/SOUFFLE-UPL.txt
 */

/************************************************************************
 *
 * @file AstProfileUse.cpp
 *
 * Implements an AstAnalysis that provides profile information
 * from a profile log file for profile-guided optimisations.
 *
 ***********************************************************************/

#include "AstProfileUse.h"
#include "AstRelationIdentifier.h"
#include "Global.h"
#include "profile/ProgramRun.h"
#include "profile/Reader.h"
#include "profile/Relation.h"
#include <limits>
#include <string>

namespace souffle {

class AstTranslationUnit;

/**
 * Run analysis, i.e., retrieve profile information
 */
void AstProfileUse::run(const AstTranslationUnit& translationUnit) {
    if (Global::config().has("profile-use")) {
        std::string filename = Global::config().get("profile-use");
        profile::Reader(filename, programRun).processFile();
    }
}

/**
 * Print analysis
 */
void AstProfileUse::print(std::ostream& os) const {}

/**
 * Check whether relation size is defined in profile
 */
bool AstProfileUse::hasRelationSize(const AstRelationIdentifier& rel) {
    return programRun->getRelation(rel.getName()) != nullptr;
}

/**
 * Get relation size from profile
 */
size_t AstProfileUse::getRelationSize(const AstRelationIdentifier& rel) {
    if (const auto* profRel = programRun->getRelation(rel.getName())) {
        return profRel->size();
    } else {
        return std::numeric_limits<size_t>::max();
    }
}

}  // end of namespace souffle
