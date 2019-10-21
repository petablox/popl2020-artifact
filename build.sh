#!/usr/bin/env bash

pushd prosynth/souffle
    ./bootstrap
    ./configure
    make -j 8
popd

