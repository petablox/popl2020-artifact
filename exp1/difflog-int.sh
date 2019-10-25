#!/usr/bin/env bash

BENCH=$1
i=$2
DATA_FILE=$3

PROBLEM_DIR=$PWD/benchmarks/regular/$BENCH

DFILE=$PWD/difflog/src/test/resources/ALPS/data/$BENCH.d
if [ ! -f "$DFILE" ]; then
    # https://linuxize.com/post/bash-check-if-file-exists/
    # $DFILE does not exist
    DFILE=$PWD/prosynth/benchmarks/curated/$BENCH/$BENCH.d
fi
if [ ! -f "$DFILE" ]; then
    DFILE=$PROBLEM_DIR/$BENCH.d
fi

TPFILE=$PWD/difflog/src/test/resources/ALPS/templates/$BENCH.tp
if [ ! -f "$TPFILE" ]; then
    TPFILE=$PWD/prosynth/benchmarks/curated/$BENCH/$BENCH.tp
fi
if [ ! -f "$TPFILE" ]; then
    TPFILE=$PROBLEM_DIR/$BENCH.tp
fi
LOG_FILE="$PWD/exp1-difflog/${BENCH}_${i}.log"

TIMEOUT=3600

cd difflog
timeout $TIMEOUT sbt "run alps $DFILE $TPFILE HybridAnnealingLearner NaiveEvaluator L2Scorer 0.01 1000000" &> $LOG_FILE
