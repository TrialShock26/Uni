FROM gcc:latest
WORKDIR /app

COPY server.c .
RUN gcc server.c -o server

ENTRYPOINT ["./server"]
# niente CMD: il server non ha bisogno di argomenti
