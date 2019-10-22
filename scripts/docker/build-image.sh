#!/usr/bin/env bash

if [ -x "$(command -v setenforce)" ]; then
    setenforce Permissive
fi

if [ -x "$(command -v systemctl)" ]; then
    systemctl start docker
fi

IMAGE_NAME=testimage

docker build -t $IMAGE_NAME .
