# continuumio/anaconda3

FROM ubuntu AS base
RUN apt-get -y update
RUN apt-get -y install build-essential
RUN apt-get -y install rsync zip openssh-server
RUN apt-get -y install cmake git tmux
RUN apt-get -y install curl
RUN apt-get -y install wget
RUN apt-get install -y python3 python3-pip python3-venv
RUN apt-get install -y build-essential libffi-dev libssl-dev

RUN python3 -m venv /opt/venv
RUN /opt/venv/bin/pip install ipython
ENV PATH="/opt/venv/bin:$PATH"
# build-base=0.5-r3
RUN apt-get update && apt-get -y install docker.io docker-compose
RUN  apt-get install -y iputils-ping

RUN apt-get clean

COPY .tmux.conf /root
# COPY src/ /app/src
# COPY test/ /app/test
# COPY run.sh /app/
# COPY build_run.sh /app/
# COPY test.sh /app/
# COPY build_run_test.sh /app/
# COPY CMakeLists.txt /app/
# WORKDIR /app
# RUN make -C src clean

