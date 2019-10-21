#!/usr/bin/env bash

# We're using the Linux Task Spooler (aka. tsp) to coordinate batch multiprocessing
# This script waits for all tasks currently in the queue to finish
# Surprisingly, the ts command itself seems to lack such a facility

while [ `tsp | wc -l` -gt 1 ]; do
    tsp -w
    tsp -C
done
