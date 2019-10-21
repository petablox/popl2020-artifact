/*
 * Souffle - A Datalog Compiler
 * Copyright (c) 2017, The Souffle Developers. All rights reserved.
 * Licensed under the Universal Permissive License v 1.0 as shown at:
 * - https://opensource.org/licenses/UPL
 * - <souffle root>/licenses/SOUFFLE-UPL.txt
 */

/************************************************************************
 *
 * @file AstPragma.cpp
 *
 * Define the class AstPragma to update global options based on parameter.
 *
 ***********************************************************************/

#include "AstPragma.h"
#include "AstProgram.h"
#include "AstTranslationUnit.h"
#include "AstVisitor.h"
#include "Global.h"
#include "Util.h"

namespace souffle {
bool AstPragmaChecker::transform(AstTranslationUnit& translationUnit) {
    bool changed = false;
    AstProgram* program = translationUnit.getProgram();

    // Take in pragma options from the command line
    if (Global::config().has("pragma")) {
        std::vector<std::string> configOptions = splitString(Global::config().get("pragma"), ';');
        for (const std::string& option : configOptions) {
            size_t splitPoint = option.find(':');

            std::string optionName = option.substr(0, splitPoint);
            std::string optionValue =
                    (splitPoint == std::string::npos) ? "" : option.substr(splitPoint + 1, option.length());

            if (!Global::config().has(optionName)) {
                changed = true;
                Global::config().set(optionName, optionValue);
            }
        }
    }

    // Take in pragma options from the datalog file itself
    visitDepthFirst(*program, [&](const AstPragma& pragma) {
        std::pair<std::string, std::string> kvp = pragma.getkvp();

        // Command line options take precedence
        if (!Global::config().has(kvp.first)) {
            changed = true;
            Global::config().set(kvp.first, kvp.second);
        }
    });

    return changed;
}
}  // end of namespace souffle
