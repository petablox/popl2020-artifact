#!/usr/bin/env bash

########################################################################################################################
# Experiment 1a: Run ProSynth (with delta analysis turned on and off respecteively) on all benchmarks
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

# 1. Prepare benchmarks

if [ -z "$SKIP_PREPARE" ]; then
    for BENCH in $BENCHES; do
        echo "Preparing $BENCH."
        PROBLEM_DIR=./benchmarks/regular/$BENCH
        tsp ./prosynth/scripts/prepare $PROBLEM_DIR
    done
    ./scripts/tsp-wait.sh
else
    echo "Skipping benchmark preparation!"
fi

# 2. Run ProSynth

if [ -z "$NUM_REPS" ]; then
    NUM_REPS=32
fi

if [ -z "$SKIP_PROSYNTH" ]; then
    mkdir -p exp1-work
    DATA_FILE=./exp1-work/data.log
    > $DATA_FILE
    for i in `seq 1 $NUM_REPS`; do
        for BENCH in $BENCHES; do
            for DELTA in 0 1; do
                echo "Running ProSynth on $BENCH. Delta $DELTA. Iteration $i."
                tsp ./exp1/prosynth-int.sh $BENCH $DELTA $i $DATA_FILE
            done
        done
    done
else
    echo "Skipping ProSynth!"
fi

exit 1

# 3. Run Difflog

if [ -z "$SKIP_DIFFLOG" ]; then
    mkdir -p exp1-difflog
    DATA_FILE=./exp1-difflog/data.log
    > $DATA_FILE
    for i in `seq 1 $NUM_REPS`; do
        for BENCH in $BENCHES; do
            echo "Running Difflog on $BENCH. Iteation $i."
            tsp ./exp1/run-difflog.sh $BENCH $i $DATA_FILE
        done
    done
else
    echo "Skipping Difflog"
fi

# 4. Run ALPS

# 5. Plot figures

./scripts/tsp-wait.sh
# TODO: Table 2
# TODO: Table 3
./exp1/plot_f6_a.py box
./exp1/plot_f6_b.py box
./exp1/plot_f8_a.py box
./exp1/plot_f8_b.py box
./exp1/plot_supf2_a.py box
./exp1/plot_supf2_b.py box
