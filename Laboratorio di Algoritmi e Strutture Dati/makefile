CC=g++-13
CFLAGS=-Wall -pedantic -O3 -std=c++20 -fsanitize=address
files=tempCode.o
filename=tempCode

all: $(filename)
	./$(filename)
$(filename): $(files)
	$(CC) $(CFLAGS) $(files) -o $@
%.o: %.cpp
	$(CC) $(CFLAGS) -c $<
clean:
	rm -rf *.o $(filename)
cleanall:
	rm -rf *.o $(filename)
run:
	./$(filename)
