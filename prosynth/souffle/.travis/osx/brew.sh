#!/bin/bash

if [ -z "$1" ];
then
  echo "No key provided"
  exit 1
fi

# set up sha256sum
brew unlink md5sha1sum
brew upgrade coreutils

#set up ssh
mkdir -p ~/.ssh
chmod 700 ~/.ssh
echo "-----BEGIN OPENSSH PRIVATE KEY-----" >~/.ssh/id_ed25519
echo "$1" >> ~/.ssh/id_ed25519
echo "-----END OPENSSH PRIVATE KEY-----" >>~/.ssh/id_ed25519
chmod 600 ~/.ssh/id_ed25519
ssh-keyscan github.com > ~/.ssh/known_hosts

# set up git user
git config --global user.name "travis-deployer"
git config --global user.email "souffle-lang@gmail.com"
git config --global push.default simple

# Enable debugging and logging of shell operations
# that are executed.
set -e
set -x

# set up brew script
for f in *.tar.gz
do
  if [ ! -e "$f" ];
  then
    echo "No tarballs found"
    exit 1
  fi

  pkg=`basename $f .tar.gz`
  sha=$(sha256sum $f|sed 's/ .*$//')

  git clone git@github.com:souffle-lang/homebrew-souffle.git
  cd homebrew-souffle/Formula

  sed -i -e "s/url \".*\"/url \"https:\/\/dl.bintray.com\/souffle-lang\/osx\/$f\"/" souffle.rb
  sed -i -e "s/sha256 \".*\"/sha256 \"$sha\"/" souffle.rb

  git add souffle.rb
  git commit -m "Update to $pkg"

  git push
done


set +e
set +x
