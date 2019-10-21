#!/bin/bash

set -oue pipefail

if [ $(which clang-format) ]
then
    clang-format \
            -i \
            -style=file \
            src/*.h \
            src/*.cpp \
            src/test/*.h \
            src/test/*.cpp \
            tests/interface/*/*.cpp
fi
