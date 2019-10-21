#!/usr/bin/env bash

########################################################################################################################
# Experiment 2: Run ProSynth (with delta analysis turned on) on various sizes of 1-object-1-type and scc
# Produces Figure 7 of the main paper and Figure 1 in the supplementary data

# Intended to be run from the root directory
# [tsp -S NUM_CORES]
# ./exp2/run.sh

########################################################################################################################
# 0. Preamble

set -e

# Trap Ctrl-C for clean exit
# https://raymii.org/s/snippets/Bash_Bits_Trap_Control_C_SIGTERM.html

function cleanup {
    tsp -K
    tsp
}
trap cleanup SIGINT
trap cleanup SIGTERM

########################################################################################################################

BENCHES='1-object-1-type scc'

# 1. Prepare benchmarks

if [ -z "$SKIP_PREPARE" ]; then
    for NUM_RULES in `seq 100 100 1000`; do
        for BENCH in $BENCHES; do
            echo "Preparing $BENCH with $NUM_RULES rules."
            PROBLEM_NAME="${BENCH}_${NUM_RULES}"
            PROBLEM_DIR=./benchmarks/scale/$PROBLEM_NAME
            tsp ./prosynth/scripts/prepare $PROBLEM_DIR
        done
    done
    ./scripts/tsp-wait.sh
else
    echo "Skipping benchmark preparation!"
fi

# 2. Run experiment

if [ -z "$NUM_REPS" ]; then
    NUM_REPS=8
fi

mkdir -p exp2-work
DATA_FILE=./exp2-work/data.log
> $DATA_FILE
for NUM_RULES in `seq 100 100 1000`; do
    for BENCH in $BENCHES; do
        for i in `seq 1 $NUM_REPS`; do
            echo "Running $BENCH with $NUM_RULES rules. Iteration $i."

            PROBLEM_NAME="${BENCH}_${NUM_RULES}"
            PROBLEM_DIR="./exp2-work/${PROBLEM_NAME}_${i}"
            LOG_FILE=$PROBLEM_DIR/log.txt

            cp -r ./benchmarks/scale/$PROBLEM_NAME $PROBLEM_DIR
            tsp ./exp2/run-int.sh $PROBLEM_DIR $i $LOG_FILE $DATA_FILE
        done
    done
done

./scripts/tsp-wait.sh

# 3. Draw figures
