# sudo setenforce Permissive
# sudo systemctl start docker
# # See https://www.youtube.com/watch?v=YFl2mCHdv24

########################################################################################################################

FROM ubuntu:18.04
ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update && \
    apt-get install -y git autoconf automake make \
                       gcc g++ mcpp \
                       python python3 openjdk-8-jdk \
                       flex bison \
                       sqlite libsqlite-dev sqlite3 libsqlite3-dev \
                       zlib1g zlib1g-dev \
                       doxygen libncurses5-dev libtool libffi-dev wget python3-matplotlib graphviz gnupg2 \
                       task-spooler procps passwd openssh-server vim curl

RUN cd root; \
    wget -c https://github.com/Z3Prover/z3/archive/z3-4.8.6.tar.gz; \
    tar -xf z3-4.8.6.tar.gz; \
    cd z3-z3-4.8.6; \
        mkdir -p /usr/local/lib/python3.6/dist-packages; \
        python scripts/mk_make.py --python --pypkgdir=/usr/local/lib/python3.6/dist-packages; \
        cd build; \
            make -j 8; \
            make install

RUN echo "deb https://dl.bintray.com/sbt/debian /" | tee -a /etc/apt/sources.list.d/sbt.list && \
    curl -sL "https://keyserver.ubuntu.com/pks/lookup?op=get&search=0x2EE0EA64E40A89B84B2DF73499E82A75642AC823" | apt-key add && \
    apt-get update && \
    apt-get install -y sbt=1.1.1

RUN git clone https://github.com/petablox/popl2020-artifact && \
    ./popl2020-artifact/scripts/build.sh

CMD /bin/bash

########################################################################################################################

# sudo docker build -t IMAGE_NAME .
# sudo docker images
# sudo docker run -it IMAGE_NAME /bin/bash

########################################################################################################################

# sudo docker images
# sudo docker rmi IMAGE_NAME
# sudo docker images
