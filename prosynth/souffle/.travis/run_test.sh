#!/bin/bash

# Enable debugging and logging of shell operations
# that are executed.
set -e
set -x

ulimit -c unlimited -S
# Run from the test directory if we don't need the unit tests
if [[ "$SOUFFLE_CATEGORY" != *"Unit"* ]]
then
  cd tests
fi
JOBS=$(nproc || sysctl -n hw.ncpu || echo 2)
TESTSUITEFLAGS="-j$JOBS $TESTRANGE" make check -j$JOBS

set +e
set +x
