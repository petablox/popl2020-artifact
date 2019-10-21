#!/bin/bash

DESCRIPTION="Translator of declarative Datalog programs into the C++ language.\
 Soufflé is a translator of declarative Datalog programs into the C++ language.\
 Soufflé is used as a domain-specific language for static program analysis, over\
 large code bases with millions of lines of code. Soufflé aims to produce\
 high-performance C++ code that can be compiled with the native compiler on\
 the target machine."

source scl_source enable devtoolset-7

# Enable debugging and logging of shell operations
# that are executed.
set -e
set -x

git fetch --tags --unshallow

./bootstrap
./configure --prefix=`pwd`/usr

JOBS=$(nproc)
make -j$JOBS install

#libstdc++ > 4.8 is not sufficient for all of C++11 but 2018/4/2 it does compile
#and all but provenance works.
#4.8 is all that's available on centos7 without workarounds
fpm -t rpm -n souffle -v `git describe --tags --always` \
    -d gcc-c++ \
    -d graphviz \
    -d libffi-devel \
    -d libgomp \
    -d 'libstdc++ >= 4.8.1' \
    -d mcpp \
    -d ncurses-devel \
    -d sqlite-devel \
    -d zlib-devel \
    -a native --description "$DESCRIPTION" \
    --url 'http://souffle-lang.org/' --license UPL -s dir usr

mkdir deploy
# compute md5 for package &
# copy files to deploy directory
for f in *.rpm
do
  pkg=`basename $f .rpm`
  src="$pkg.rpm"
  dest="deploy/$pkg.rpm"
  cp $src $dest
  md5sum <$src >deploy/$pkg.md5
done

# show contents of deployment
ls deploy/*
