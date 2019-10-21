#!/bin/sh

travis_retry() {
  local result=0
  local count=1
  while [ $count -le 3 ]; do
    [ $result -ne 0 ] && {
      echo -e "\n${ANSI_RED}The command \"$@\" failed. Retrying, $count of 3.${ANSI_RESET}\n" >&2
    }
    "$@"
    result=$?
    [ $result -eq 0 ] && break
    count=$(($count + 1))
    sleep 1
  done

  [ $count -gt 3 ] && {
    echo -e "\n${ANSI_RED}The command \"$@\" failed 3 times.${ANSI_RESET}\n" >&2
  }

  return $result
}

# Add our repo to get mcpp
travis_retry yum install -y https://dl.bintray.com/souffle-lang/rpm-unstable/centos/7/x86_64/souffle-repo-centos-1.0.2-1.x86_64.rpm

# Build dependencies
travis_retry yum install -y -q autoconf automake bison clang doxygen flex gcc gcc-c++ git kernel-devel libffi-devel libtool make mcpp ncurses-devel python sqlite sqlite-devel sudo zlib-devel

# Set up a more recent gcc that supports C++11
travis_retry yum install -y centos-release-scl
travis_retry yum install -y devtoolset-7-gcc-c++

# Set up the package builder
travis_retry yum install -y -q rpm-build ruby-devel
travis_retry gem install --no-ri --no-rdoc rake
travis_retry gem install --no-ri --no-rdoc fpm

fpm --version
