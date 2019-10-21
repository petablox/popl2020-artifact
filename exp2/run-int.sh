#!/usr/bin/env bash

BENCH=$1
NUM_RULES=$2
i=$3
DATA_FILE=$4

PROBLEM_NAME="${BENCH}_${NUM_RULES}"
PROBLEM_DIR="./exp2-work/${PROBLEM_NAME}_${i}"
LOG_FILE=$PROBLEM_DIR/log.txt

cp -r ./benchmarks/scale/$PROBLEM_NAME $PROBLEM_DIR
./prosynth/scripts/prosynth $PROBLEM_DIR 0 1 $DATA_FILE &> $LOG_FILE
