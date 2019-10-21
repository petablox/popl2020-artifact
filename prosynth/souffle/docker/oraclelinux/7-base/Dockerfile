FROM oraclelinux:7

WORKDIR /tmp

# Add souffle repo to get mcpp
RUN curl -O https://dl.bintray.com/souffle-lang/rpm-unstable/centos/7/x86_64/souffle-repo-centos-1.0.2-1.x86_64.rpm
RUN yum install -y souffle-repo-centos-1.0.2-1.x86_64.rpm

RUN yum install -y \
        autoconf \
        automake \
        bison \
        doxygen \
        flex \
        gcc-c++ \
        git \
        graphviz \
        kernel-devel \
        libffi-devel \
        libtool \
        make \
        mcpp \
        ncurses-devel \
        sqlite \
        sqlite-devel \
        zlib-devel

RUN useradd --create-home --shell /bin/bash souffle

USER souffle

WORKDIR /home/souffle
