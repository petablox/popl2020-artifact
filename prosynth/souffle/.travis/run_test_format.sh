#!/bin/bash

# Enable debugging and logging of shell operations
# that are executed.
set -e
set -x

#clang-format --version
$(dirname $0)/checkStyle.sh HEAD~
