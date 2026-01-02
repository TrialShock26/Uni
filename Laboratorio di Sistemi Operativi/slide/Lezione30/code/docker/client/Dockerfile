FROM ubuntu:22.04

RUN apt update && apt install -y gcc

WORKDIR /app
COPY client.c .

RUN gcc client.c -o client

# Il comando da eseguire è SOLO questo
ENTRYPOINT ["./client"]

# Qui metti SOLO gli argomenti di default (hostname, porta)
CMD ["server-cont"]
