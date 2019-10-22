# sudo setenforce Permissive
# sudo systemctl start docker

########################################################################################################################

FROM fedora:30

RUN dnf install -y git autoconf automake make \
                   gcc gcc-c++ mcpp \
                   python python3 \
                   flex bison \
                   sqlite sqlite-devel zlib zlib-devel \
                   z3 z3-devel python3-z3 \
                   doxygen ncurses ncurses-devel libtool libffi libffi-devel wget python3-matplotlib graphviz \
                   task-spooler which
RUN curl https://bintray.com/sbt/rpm/rpm > /etc/yum.repos.d/bintray-sbt-rpm.repo
RUN dnf install -y java java-devel sbt-1.1.1

RUN git clone https://github.com/petablox/popl2020-artifact
RUN ./popl2020-artifact/scripts/build.sh

########################################################################################################################

# sudo docker build -t IMAGE_NAME .
# sudo docker images
# sudo docker run -it IMAGE_NAME /bin/bash

########################################################################################################################

# sudo docker images
# sudo docker rmi IMAGE_NAME
# sudo docker images