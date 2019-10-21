#!/bin/bash

# Enable debugging and logging of shell operations
# that are executed.
set -e
set -x

# create deployment directory
mkdir deploy

JOBS=$(sysctl -n hw.ncpu)
make -j$JOBS package

# compute md5 for package &
# copy files to deploy directory
for f in *.pkg
do
  pkg=`basename $f .pkg`
  src="$pkg.pkg"
  dest="deploy/$pkg.pkg"
  cp $src $dest
  md5sum <$src >deploy/$pkg.md5
done
# show contents of deployment
ls deploy/*

#Create tarball for brew
make dist

set +x
set +e
