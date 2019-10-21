#!/usr/bin/env bash

PROBLEM_DIR=$1
i=$2
LOG_FILE=$3
./prosynth/scripts/prosynth $PROBLEM_DIR 0 1 $i > $LOG_FILE
