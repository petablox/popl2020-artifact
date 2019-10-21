/*
 * Souffle - A Datalog Compiler
 * Copyright (c) 2019, The Souffle Developers. All rights reserved.
 * Licensed under the Universal Permissive License v 1.0 as shown at:
 * - https://opensource.org/licenses/UPL
 * - <souffle root>/licenses/SOUFFLE-UPL.txt
 */

/************************************************************************
 *
 * @file InterpreterRecords.cpp
 *
 * Utilities for handling records in Interpreter
 *
 ***********************************************************************/

#include "InterpreterRecords.h"
#include <cassert>
#include <limits>
#include <map>
#include <unordered_map>
#include <vector>

namespace souffle {

namespace {

using namespace std;

/**
 * A bidirectional mapping between tuples and reference indices.
 */
class InterpreterRecordMap {
    /** The arity of the stored tuples */
    int arity;

    /** The mapping from tuples to references/indices */
    map<vector<RamDomain>, RamDomain> r2i;

    /** The mapping from indices to tuples */
    vector<vector<RamDomain>> i2r;

public:
    InterpreterRecordMap(int arity) : arity(arity), i2r(1) {}  // note: index 0 element left free

    /**
     * Packs the given tuple -- and may create a new reference if necessary.
     */
    RamDomain pack(const RamDomain* tuple) {
        vector<RamDomain> tmp(arity);
        for (int i = 0; i < arity; i++) {
            tmp[i] = tuple[i];
        }

        RamDomain index;
#pragma omp critical(record_pack)
        {
            auto pos = r2i.find(tmp);
            if (pos != r2i.end()) {
                index = pos->second;
            } else {
#pragma omp critical(record_unpack)
                {
                    i2r.push_back(tmp);
                    index = i2r.size() - 1;
                    r2i[tmp] = index;

                    // assert that new index is smaller than the range
                    assert(index != std::numeric_limits<RamDomain>::max());
                }
            }
        }

        return index;
    }

    /**
     * Obtains a pointer to the tuple addressed by the given index.
     */
    RamDomain* unpack(RamDomain index) {
        RamDomain* res;

#pragma omp critical(record_unpack)
        res = &(i2r[index][0]);

        return res;
    }
};

/**
 * The static access function for record maps of certain arities.
 */
InterpreterRecordMap& getForArity(int arity) {
    // the static container -- filled on demand
    static unordered_map<int, InterpreterRecordMap> maps;
    auto pos = maps.find(arity);
    if (pos == maps.end()) {
        maps.emplace(arity, arity);
    }

    return maps.find(arity)->second;
}
}  // namespace

RamDomain packInterpreter(RamDomain* tuple, int arity) {
    // conduct the packing
    return getForArity(arity).pack(tuple);
}

RamDomain* unpackInterpreter(RamDomain ref, int arity) {
    // conduct the unpacking
    return getForArity(arity).unpack(ref);
}

RamDomain getNullInterpreter() {
    return 0;
}

bool isNullInterpreter(RamDomain ref) {
    return ref == 0;
}

void createRecordMap(int arity) {
    getForArity(arity);
}

}  // end of namespace souffle
