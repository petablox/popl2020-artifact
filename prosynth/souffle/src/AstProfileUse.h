/*
 * Souffle - A Datalog Compiler
 * Copyright (c) 2018, The Souffle Developers. All rights reserved
 * Licensed under the Universal Permissive License v 1.0 as shown at:
 * - https://opensource.org/licenses/UPL
 * - <souffle root>/licenses/SOUFFLE-UPL.txt
 */

/************************************************************************
 *
 * @file AstProfileUse.h
 *
 * Defines a simple class to query profile data from a profile
 * for profile-guided optimisation.
 *
 ***********************************************************************/

#pragma once

#include "AstAnalysis.h"
#include "AstRelationIdentifier.h"
#include "profile/ProgramRun.h"
#include <cstddef>
#include <iostream>
#include <memory>

namespace souffle {

/**
 * AstAnalysis that loads profile data and has a profile query interface.
 */
class AstProfileUse : public AstAnalysis {
private:
    /** performance model of profile run */
    std::shared_ptr<profile::ProgramRun> programRun;

public:
    /** Name of analysis */
    static constexpr const char* name = "profile-use";

    AstProfileUse() : programRun(std::make_shared<profile::ProgramRun>(profile::ProgramRun())) {}

    /** Run analysis */
    void run(const AstTranslationUnit& translationUnit) override;

    /** Output some profile information */
    void print(std::ostream& os) const override;

    /** Check whether the relation size exists in profile */
    bool hasRelationSize(const AstRelationIdentifier& rel);

    /** Return size of relation in the profile */
    size_t getRelationSize(const AstRelationIdentifier& rel);
};

}  // end of namespace souffle
