FROM ubuntu:bionic

WORKDIR /tmp

RUN apt-get update -y && \
        apt-get upgrade -y && \
        apt-get install -y \
        curl \
        software-properties-common

RUN apt-get update -y && \
        apt-get upgrade -y && \
        apt-get install -y \
        automake \
        autoconf \
        bison \
        build-essential \
        doxygen \
        flex \
        g++ \
        git \
        graphviz \
        libffi-dev \
        libncurses5-dev \
        libopenmpi-dev \
        libsqlite3-dev \
        libtool \
        lsb-release \
        mcpp \
        openmpi-bin \
        zlib1g-dev

RUN useradd --create-home --shell /bin/bash souffle

USER souffle

WORKDIR /home/souffle
