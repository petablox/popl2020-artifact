#!/usr/bin/env bash

BENCH=$1
i=$2
DATA_FILE=$3

PROBLEM_DIR=$PWD/benchmarks/regular/$BENCH
LOG_FILE="$PWD/exp1-difflog/${BENCH}_${i}.log"

TIMEOUT=3600 # TODO! 3600

cd difflog
timeout $TIMEOUT sbt "run alps $PROBLEM_DIR/$BENCH.d $PROBLEM_DIR/$BENCH.tp HybridAnnealingLearner NaiveEvaluator L2Scorer 0.01 1000" &> $LOG_FILE
