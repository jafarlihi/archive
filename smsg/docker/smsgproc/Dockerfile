FROM debian:jessie-slim
MAINTAINER Hikmat Jafarli <jafarlihi@gmail.com>

COPY instantclient/* /tmp/

RUN apt-get update && apt-get install -y alien libaio1 && \
    alien -iv /tmp/oracle-instantclient12.2-basiclite-12.2.0.1.0-1.x86_64.rpm && \
    alien -iv /tmp/oracle-instantclient12.2-devel-12.2.0.1.0-1.x86_64.rpm && \
    apt-get purge -y alien perl perl5 && apt-get -y autoremove && apt-get clean && \
    rm -rf /tmp/oracle-* && rm -rf /usr/share/docs && rm -rf /usr/share/man 

ENV ORACLE_HOME=/usr/lib/oracle/12.2/client64
ENV LD_LIBRARY_PATH=$ORACLE_HOME/lib
ENV PATH=$ORACLE_HOME/bin:$PATH

COPY ./smsgproc /home

EXPOSE 9090

WORKDIR /home
ENTRYPOINT ["./smsgproc"]
