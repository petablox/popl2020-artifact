#!/bin/bash

# Enable debugging and logging of shell operations
# that are executed.
set -e
set -x

# Install requirements of MAC OS X
. .travis/osx/install.sh

rm /usr/local/include/c++ || true

brew install gcc@9

# Using 'g++' will call the xcode link to clang
export CC=gcc-9
export CXX=g++-9

$CXX --version
$CC --version

set +e
set +x
