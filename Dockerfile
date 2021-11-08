FROM ubuntu:latest
ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update;                                                                         \
    apt-get install -y build-essential cmake clang-12 libclang-12-dev qt5-default;          \
    mkdir -p /usr/src;                                                            

COPY . /usr/src/StaticCouplingTool

RUN cd /usr/src/StaticCouplingTool;  \
    cmake .; make