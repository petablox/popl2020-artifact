#!/usr/bin/env bash

pushd popl2020-artifact
    pushd prosynth/souffle
        ./bootstrap
        ./configure
        make -j 8
    popd

    pushd difflog
        sbt compile
    popd

    pushd alps
        make -j 4
    popd
popd

