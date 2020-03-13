CC=gcc
C_FLAGS=-O3 -fno-stack-protector -no-pie -static -Wall -mavx -Iinclude/ -g
INC=-lm

all: tsp

bin/array.o: src/array.c
	$(CC) $(C_FLAGS) -c $^ -o $@ $(INC)

bin/driver.o: src/driver.c
	$(CC) $(C_FLAGS) -c $^ -o $@ $(INC)

bin/io.o: src/io.c
	$(CC) $(C_FLAGS) -c $^ -o $@ $(INC)

bin/tsp.o: src/tsp.c
	$(CC) $(C_FLAGS) -c $^ -o $@ $(INC)

tsp: bin/driver.o bin/io.o bin/tsp.o bin/array.o
	$(CC) $(C_FLAGS) $^ -o $@ $(INC)

clean:
	$(RM) tsp bin/*
