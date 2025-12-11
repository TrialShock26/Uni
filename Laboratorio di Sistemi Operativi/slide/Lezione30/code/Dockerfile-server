FROM gcc:latest
WORKDIR /app

COPY server.c .
RUN gcc server.c -o server-bin

ENTRYPOINT ["./server-bin"]
# niente CMD: il server non ha bisogno di argomenti
