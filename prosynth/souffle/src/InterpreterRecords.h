/*
 * Souffle - A Datalog Compiler
 * Copyright (c) 2019, The Souffle Developers. All rights reserved.
 * Licensed under the Universal Permissive License v 1.0 as shown at:
 * - https://opensource.org/licenses/UPL
 * - <souffle root>/licenses/SOUFFLE-UPL.txt
 */

/************************************************************************
 *
 * @file InterpreterRecords.h
 *
 * Utilities for handling records in the Interpreter
 *
 ***********************************************************************/

#pragma once

#include "RamTypes.h"

namespace souffle {

/**
 * A function packing a tuple of the given arity into a reference.
 */
RamDomain packInterpreter(RamDomain* tuple, int arity);

/**
 * A function obtaining a pointer to the tuple addressed by the given reference.
 */
RamDomain* unpackInterpreter(RamDomain ref, int arity);

/**
 * Obtains the null-reference constant.
 */
RamDomain getNullInterpreter();

/**
 * Determines whether the given reference is the null reference encoding
 * the absence of any nested record.
 */
bool isNullInterpreter(RamDomain ref);

/**
 * Create a record entry with given arity in the static container file InterpreterRecord.cpp
 */
void createRecordMap(int arity);

}  // end of namespace souffle
