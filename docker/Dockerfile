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
                   doxygen ncurses ncurses-devel libtool wget python3-matplotlib \
                   task-spooler which
RUN curl https://bintray.com/sbt/rpm/rpm > /etc/yum.repos.d/bintray-sbt-rpm.repo
RUN dnf install -y java java-devel sbt-1.1.1

RUN git clone https://github.com/petablox/popl2020-artifact
RUN cd popl2020-artifact/prosynth/souffle && ./boostrap && ./configure && make -j 4

########################################################################################################################

# sudo docker build -t IMAGE_NAME .
# sudo docker images
# sudo docker run -it IMAGE_NAME /bin/bash

########################################################################################################################

# dnf install -y git autoconf automake make \
#                gcc gcc-c++ mcpp \
#                python python3 \
#                flex bison \
#                sqlite sqlite-devel zlib zlib-devel \
#                z3 z3-devel python3-z3 \
#                doxygen ncurses ncurses-devel libtool wget python3-matplotlib \
#                task-spooler which

# # # https://computingforgeeks.com/how-to-install-java-13-on-centos-fedora/
# # cd /home
# # wget -c https://download.java.net/java/GA/jdk13.0.1/cec27d702aa74d5a8630c65ae61e4305/9/GPL/openjdk-13.0.1_linux-x64_bin.tar.gz
# # tar -xf openjdk-13.0.1_linux-x64_bin.tar.gz
# # mv jdk-13.0.1 /opt/
# ...

# dnf install -y java java-devel
# curl https://bintray.com/sbt/rpm/rpm > bintray-sbt-rpm.repo
# mv bintray-sbt-rpm.repo /etc/yum.repos.d/
# dnf install sbt-1.1.1

########################################################################################################################

# sudo docker images
# sudo docker rmi IMAGE_NAME
# sudo docker images
