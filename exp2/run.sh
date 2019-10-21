#!/usr/bin/env bash

BENCHES='1-object-1-type scc'

# 1. Prepare benchmarks

for BENCH in $BENCHES; do
    for NUM_RULES in `seq 100 100 1000`; do
        PROBLEM_DIR="${BENCH}_${NUM_RULES}"
        echo "Preparing $PROBLEM_DIR"
        ./prosynth/scripts/prepare $PROBLEM_DIR
    done
done

# 2. Run experiments

touch data.log

for BENCH in $BENCHES; do
    for NUM_RULES in `seq 100 100 1000`; do
        echo "${BENCH}_${NUM_RULES}"
        # echo $NUM_RULES
    done
done
