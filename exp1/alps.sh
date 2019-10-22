#!/usr/bin/env bash

########################################################################################################################
# Experiment 1a: Run ALPS on all benchmarks
# Produces Tables 2 and 3 and Figures 6b and 8 of the main paper
# Also produces Figure 2 from the supplementary data

# Intended to be run from the root directory
# ./exp1/prosynth.sh NUM_CORES

########################################################################################################################
# 0. Preamble

set -e

########################################################################################################################

mkdir -p exp1-alps
cd alps
./scripts/run.py ./alps ./data ./data/templates ../exp1-alps
cd ..
./exp1/gent2_alps.py exp1-alps

