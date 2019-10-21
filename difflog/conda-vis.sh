#!/usr/bin/env bash
conda create -n qd_vis python=3
source activate qd_vis
conda install numpy hdf5
pip install hypertools
