FROM ubuntu
MAINTAINER Tarun Chinmai
RUN apt-get update && \ 
	apt-get upgrade -y && \
	apt-get install -y build-essential mpich2 python-dev python-pip zlib1g-dev
RUN pip install mpi4py

