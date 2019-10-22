#!/usr/bin/env bash

########################################################################################################################
# Experiment 1b: Run Difflog on all benchmarks
# Produces Tables 2 and 3 and Figures 6b and 8 of the main paper
# Also produces Figure 2 from the supplementary data

# Intended to be run from the root directory
# ./exp1/prosynth.sh NUM_CORES

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

NUM_CORES=$1
tsp -S $NUM_CORES

########################################################################################################################

BENCHES='1-call-site 1-object 1-object-1-type 1-type 2-call-site abduce andersen animals buildwall clique cliquer '
BENCHES+='downcast escape inflamation modref nearlyscc path polysite rsg rvcheck scc sgen ship small '
BENCHES+='sql-01 sql-02 sql-03 sql-04 sql-05 sql-06 sql-07 sql-08 sql-09 sql-10 sql-11 sql-12 sql-13 sql-14 sql-15 '
BENCHES+='traffic union-find'

if [ -z "$NUM_REPS" ]; then
    NUM_REPS=32
fi

mkdir -p exp1-difflog

for i in `seq 1 32`; do
    for BENCH in $BENCHES; do
        echo "Running Difflog on $BENCH. Iteration $i."
        tsp ./exp1/difflog-int.sh $BENCH $i $DATA_FILE
    done
done
