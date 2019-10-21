FROM centos:centos7

WORKDIR /tmp

RUN yum -y install epel-release

# Add souffle repo to get mcpp
RUN curl -O https://dl.bintray.com/souffle-lang/rpm-unstable/centos/7/x86_64/souffle-repo-centos-1.0.2-1.x86_64.rpm
RUN yum install -y souffle-repo-centos-1.0.2-1.x86_64.rpm

RUN yum -y install \
        automake \
        autoconf \
        bison \
        doxygen \
        flex \
        gcc-c++ \
        git \
        graphviz \
        libffi-devel \
        libtool \
        libsqlite3x-devel \
        make \
        mcpp \
        ncurses-devel \
        zlib-devel

RUN useradd --create-home --shell /bin/bash souffle

USER souffle

WORKDIR /home/souffle
