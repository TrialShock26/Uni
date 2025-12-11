FROM ubuntu:22.04

RUN apt update && apt install -y gcc

WORKDIR /app
COPY client-bin.c .

RUN gcc client-bin.c -o client-bin

# Il comando da eseguire è SOLO questo
ENTRYPOINT ["./client-bin"]

# Qui metti SOLO gli argomenti di default (hostname, porta)
CMD ["server-cont"]
