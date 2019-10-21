#!/usr/bin/env bash

PROBLEM_DIR=$1
i=$2
LOG_FILE=$3
DATA_FILE=$4
./prosynth/scripts/prosynth $PROBLEM_DIR 0 1 $DATA_FILE &> $LOG_FILE
