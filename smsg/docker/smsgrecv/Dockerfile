FROM debian:jessie-slim
MAINTAINER Hikmat Jafarli <jafarlihi@gmail.com>

COPY ../../src/smsgrecv/redis-lua /home/redis-lua
COPY ./smsgrecv /home

EXPOSE 9090

WORKDIR /home
ENTRYPOINT ["./smsgrecv"]
