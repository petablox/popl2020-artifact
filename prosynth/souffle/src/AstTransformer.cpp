/*
 * Souffle - A Datalog Compiler
 * Copyright (c) 2015, Oracle and/or its affiliates. All rights reserved
 * Licensed under the Universal Permissive License v 1.0 as shown at:
 * - https://opensource.org/licenses/UPL
 * - <souffle root>/licenses/SOUFFLE-UPL.txt
 */

/************************************************************************
 *
 * @file AstTransformer.cpp
 *
 * Defines the interface for AST transformation passes.
 *
 ***********************************************************************/

#include "AstTransformer.h"
#include "AstTranslationUnit.h"
#include "ErrorReport.h"
#include <chrono>
#include <cstdlib>
#include <iostream>

namespace souffle {

bool AstTransformer::apply(AstTranslationUnit& translationUnit) {
    bool changed = transform(translationUnit);
    if (changed) {
        translationUnit.invalidateAnalyses();
    }
    return changed;
}

bool MetaTransformer::applySubtransformer(AstTranslationUnit& translationUnit, AstTransformer* transformer) {
    auto start = std::chrono::high_resolution_clock::now();
    bool changed = transformer->apply(translationUnit);
    auto end = std::chrono::high_resolution_clock::now();

    if (verbose && !dynamic_cast<MetaTransformer*>(transformer)) {
        std::string changedString = changed ? "changed" : "unchanged";
        std::cout << transformer->getName() << " time: " << std::chrono::duration<double>(end - start).count()
                  << "sec [" << changedString << "]" << std::endl;
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
