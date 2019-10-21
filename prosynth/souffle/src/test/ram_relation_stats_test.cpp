/*
 * Souffle - A Datalog Compiler
 * Copyright (c) 2013, 2015, Oracle and/or its affiliates. All rights reserved
 * Licensed under the Universal Permissive License v 1.0 as shown at:
 * - https://opensource.org/licenses/UPL
 * - <souffle root>/licenses/SOUFFLE-UPL.txt
 */

/************************************************************************
 *
 * @file ram_relation_stats_test.h
 *
 * Tests for the ram relation statistics extraction utility.
 *
 ***********************************************************************/

#include "IOSystem.h"
#include "Interpreter.h"
#include "ReadStream.h"
#include "test.h"

#include <fstream>
#include <memory>

using namespace souffle;

namespace test {

TEST(Stats, Basic) {
    // create a table
    InterpreterRelation rel(3);

    // add some values
    rel.insert(1, 1, 1);
    rel.insert(1, 2, 1);
    rel.insert(1, 3, 2);
    rel.insert(1, 4, 2);

    RelationStats stats = RelationStats::extractFrom(rel);

    EXPECT_EQ(1, stats.getEstimatedCardinality(0));
    EXPECT_EQ(4, stats.getEstimatedCardinality(1));
    EXPECT_EQ(2, stats.getEstimatedCardinality(2));
}

TEST(Stats, Function) {
    // create a table
    InterpreterRelation rel(2);

    // add some values
    for (int i = 0; i < 10000; i++) {
        rel.insert(i, i % 5);
    }

    RelationStats stats = RelationStats::extractFrom(rel, 100);

    EXPECT_EQ(100, stats.getSampleSize());
    EXPECT_EQ(10000, stats.getCardinality());

    EXPECT_EQ(10000, stats.getEstimatedCardinality(0));
    EXPECT_EQ(500, stats.getEstimatedCardinality(1));
}

TEST(Stats, Convergence) {
    // load a table
    InterpreterRelation rel(2);

    SymbolTable symTable;

    SymbolMask mask(2);
    mask.setSymbol(0);
    mask.setSymbol(1);

    {
        std::fstream in(BUILDDIR "../tests/evaluation/hmmer/facts/DirectFlow.facts");

        IODirectives ioDirectives(
                {{"IO", "file"}, {"filename", BUILDDIR "../tests/evaluation/hmmer/facts/DirectFlow.facts"},
                        {"delimiter", "\t"}});
        // if file not found => be done
        if (!in.is_open()) return;

        std::unique_ptr<ReadStream> reader =
                IOSystem::getInstance().getReader(mask, symTable, ioDirectives, false);
        reader->readAll(rel);
    }

    std::cout << rel.size() << "\n";

    InterpreterRelation rel2(3);

    for (const auto& cur : rel) {
        rel2.insert(cur[0], cur[1], 1);
    }

    RelationStats full = RelationStats::extractFrom(rel2);

    RelationStats s10 = RelationStats::extractFrom(rel2, 10);
    RelationStats s100 = RelationStats::extractFrom(rel2, 100);
    RelationStats s1000 = RelationStats::extractFrom(rel2, 1000);
    RelationStats s10000 = RelationStats::extractFrom(rel2, 10000);

    for (int i = 0; i < 3; i++) {
        std::cout << "Card " << i << ":\n";
        std::cout << "\t" << s10.getEstimatedCardinality(i) << " - "
                  << (s10.getEstimatedCardinality(i) - full.getEstimatedCardinality(i)) << "\n";
        std::cout << "\t" << s100.getEstimatedCardinality(i) << " - "
                  << (s100.getEstimatedCardinality(i) - full.getEstimatedCardinality(i)) << "\n";
        std::cout << "\t" << s1000.getEstimatedCardinality(i) << " - "
                  << (s1000.getEstimatedCardinality(i) - full.getEstimatedCardinality(i)) << "\n";
        std::cout << "\t" << s10000.getEstimatedCardinality(i) << " - "
                  << (s10000.getEstimatedCardinality(i) - full.getEstimatedCardinality(i)) << "\n";
        std::cout << "\t" << full.getEstimatedCardinality(i) << " - "
                  << (full.getEstimatedCardinality(i) - full.getEstimatedCardinality(i)) << "\n";

        std::cout << "\n";
    }
}

}  // end namespace test
