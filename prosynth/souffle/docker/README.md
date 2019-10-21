# souffle-docker

[Docker](https://www.docker.com/) images for [Soufflé](https://github.com/souffle-lang/souffle).

This is the development repository for the official Soufflé account on Dockerhub, found [here](https://hub.docker.com/r/souffle).

## Installation

If all you want to do is run Soufflé in a Docker container, then simply use any of the images in the official Soufflé account on Dockerhub.

For example, if you wanted to run souffle for Ubuntu, specifically version xenial, you would do

~~~
$ docker run souffle/ubuntu:xenial
~~~

Which will pull the container from Dockerhub and run it.

## Usage

A more useful way to do things is

~~~
$ docker run -v${PWD}:/mnt -it souffle/ubuntu:xenial /bin/bash
~~~

Which will enter a bash shell in the container, with your current working directory mounted at `/mnt`.

From here, it is as simple as running

~~~
$ souffle
~~~

To invoke Soufflé.

## Development

If you want to actually develop souffle-docker itself, then you'll need to learn some commands, and how to configure them.

### Commands

The commands are provided by a simple Makefile, and are explained as follows.

~~~
$ make
~~~

This will build one image per Dockerfile in this repository.

For a Dockerfile at `./path/to/Dockerfile`, relative to the root of this repository, the tag of the corresponding image would be `souffle/path:to`.

New Dockerfiles can be added by following this directory structure, and will be detected automatically.

~~~
$ make check
~~~

This will run the Soufflé testsuite for each of the Docker images.

Specific test categories and command line flags to use may be configured as described below, and this functionality may be used in future for CI testing with Travis.

~~~
$ make deploy
~~~

This will deploy the Docker images to an account on Dockerhub, if you have authorisation for that account.

### Configuration

All configuration is done through environment variables.

Defaults are defined at the top of the Makefile, and in each Dockerfile.

These may be overriden within individual Dockerfiles for reasons specific to them.

They are explained as follows:

- `SOUFFLE_CATEGORY`: The test categories to be used in a call to `make check`.
- `SOUFFLE_CONFIGURE_OPTIONS`: The arguments passed to `./configure` when building Soufflé in a call to `make`.
- `SOUFFLE_CONFS`: The command line flags to be used for Soufflé in a call to `make check`.
- `SOUFFLE_CC`: The value of the `CC` environment variable used in Dockerfiles.
- `SOUFFLE_CXX`: The value of the `CXX` environment variable used in Dockerfiles.
- `SOUFFLE_DOCKERFILES`: A list of paths to Dockerfile's in this repository, which determine all those that are considered in any `make` command.
- `SOUFFLE_DOCKERHUB_USER`: The username of the Dockerhub account to use in a call to `make deploy`.
- `SOUFFLE_GITHUB_USER`: The username of the Github repository from which Soufflé will be pulled in a call to `make`.
- `SOUFFLE_GIT_BRANCH`: The git branch used when building the images in a call to `make`.
- `SOUFFLE_GIT_REVISION`: The commit SHA of the git revision, or `HEAD` to use the latest commit, used in a call to `make`.
- `SOUFFLE_MAKE_JOBS`: The number of jobs for each `make` command within a Dockerfile (i.e. with the `-j` option).
