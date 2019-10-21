/*
 * Souffle - A Datalog Compiler
 * Copyright (c) 2015, Oracle and/or its affiliates. All rights reserved
 * Licensed under the Universal Permissive License v 1.0 as shown at:
 * - https://opensource.org/licenses/UPL
 * - <souffle root>/licenses/SOUFFLE-UPL.txt
 */

/************************************************************************
 *
 * @file RamTransformer.cpp
 *
 * Defines the interface for RAM transformation passes.
 *
 ***********************************************************************/

#include "RamTransformer.h"
#include "RamTranslationUnit.h"

#include <algorithm>

namespace souffle {

bool RamTransformer::apply(RamTranslationUnit& translationUnit) {
    // take snapshot of alive analyses before invocation
    std::set<const RamAnalysis*> beforeInvocation = translationUnit.getAliveAnalyses();

    // invoke the transformation
    bool changed = transform(translationUnit);

    // take snapshot of alive analyses after invocation
    std::set<const RamAnalysis*> afterInvocation = translationUnit.getAliveAnalyses();

    // print newly invoked analyses (not for meta transformers)
    if (nullptr == dynamic_cast<RamMetaTransformer*>(this)) {
        for (const RamAnalysis* analysis : afterInvocation) {
            if (0 == beforeInvocation.count(analysis)) {
                std::stringstream ramAnalysisStr;
                analysis->print(ramAnalysisStr);
                if (!ramAnalysisStr.str().empty()) {
                    translationUnit.getDebugReport().addSection(DebugReporter::getCodeSection(
                            getName(), "RAM Analysis " + analysis->getName(), ramAnalysisStr.str()));
                }
            }
        }
    }

    if (changed) {
        translationUnit.invalidateAnalyses();
        std::stringstream ramProgStr;
        ramProgStr << *translationUnit.getProgram();
        translationUnit.getDebugReport().addSection(
                DebugReporter::getCodeSection(getName(), "RAM Program after " + getName(), ramProgStr.str()));

    } else {
        translationUnit.getDebugReport().addSection(
                DebugReportSection(getName(), "After " + getName() + " " + " (unchanged)", {}, ""));
    }

    /* Abort evaluation of the program if errors were encountered */
    if (translationUnit.getErrorReport().getNumErrors() != 0) {
        std::cerr << translationUnit.getErrorReport();
        std::cerr << std::to_string(translationUnit.getErrorReport().getNumErrors()) +
                             " errors generated, evaluation aborted"
                  << std::endl;
        exit(1);
    }
    return changed;
}

}  // end of namespace souffle
