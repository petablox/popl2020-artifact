#!/bin/bash

# Enable debugging and logging of shell operations
# that are executed.
set -e
set -x

# create deployment directory
mkdir deploy

JOBS=$(nproc)
make -j$JOBS package

# compute md5 for package &
# copy files to deploy directory
for f in packaging/*.deb
do
  pkg=`basename $f .deb`
  src="packaging/$pkg.deb"
  dest="deploy/$pkg.deb"
  cp $src $dest
  md5sum <$src >deploy/$pkg.md5
done
# show contents of deployment
ls deploy/*
