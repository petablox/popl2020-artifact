/*
 * Souffle - A Datalog Compiler
 * Copyright (c) 2019, The Souffle Developers. All rights reserved.
 * Licensed under the Universal Permissive License v 1.0 as shown at:
 * - https://opensource.org/licenses/UPL
 * - <souffle root>/licenses/SOUFFLE-UPL.txt
 */

/************************************************************************
 *
 * @file AstIOTypeAnalysis.h
 *
 * Implements methods to identify a relation as input, output, or printsize.
 *
 ***********************************************************************/

#include "AstIOTypeAnalysis.h"
#include "AstIO.h"
#include "AstRelation.h"
#include "AstTranslationUnit.h"
#include "AstVisitor.h"

namespace souffle {

void IOType::run(const AstTranslationUnit& translationUnit) {
    visitDepthFirst(*translationUnit.getProgram(), [&](const AstLoad& directive) {
        if (directive.getNames().empty()) {
            return;
        }

        auto* relation = translationUnit.getProgram()->getRelation(directive.getName());
        if (relation == nullptr) {
            return;
        }

        inputRelations.insert(relation);
    });
    visitDepthFirst(*translationUnit.getProgram(), [&](const AstStore& directive) {
        if (directive.getNames().empty()) {
            return;
        }

        auto* relation = translationUnit.getProgram()->getRelation(directive.getName());
        if (relation == nullptr) {
            return;
        }

        outputRelations.insert(relation);
    });
    visitDepthFirst(*translationUnit.getProgram(), [&](const AstPrintSize& directive) {
        if (directive.getNames().empty()) {
            return;
        }

        auto* relation = translationUnit.getProgram()->getRelation(directive.getName());
        if (relation == nullptr) {
            return;
        }

        printSizeRelations.insert(relation);
    });
}

void IOType::print(std::ostream& os) const {
    os << "input relations: " << inputRelations << std::endl;
    os << "output relations: " << outputRelations << std::endl;
    os << "printSize relations: " << printSizeRelations << std::endl;
}

}  // end of namespace souffle
