CC=gcc
C_FLAGS=-O3 -fno-stack-protector -no-pie -static

all: tsp

tsp: tsp.c
	$(CC) $(C_FLAGS) $^ -o $@

clean:
	$(RM) tsp
