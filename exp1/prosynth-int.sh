#!/usr/bin/env bash

BENCH=$1
DO_DELTA=$2
i=$3
DATA_FILE=$4

mkdir -p ./exp1-work/$BENCH
PROBLEM_DIR="./exp1-work/${BENCH}/D${DO_DELTA}_I${i}"
LOG_FILE=$PROBLEM_DIR/log.txt

cp -r ./benchmarks/regular/$BENCH $PROBLEM_DIR
./prosynth/scripts/prosynth $PROBLEM_DIR 0 $DO_DELTA $DATA_FILE &> $LOG_FILE
