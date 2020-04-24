all: scheduler

CC=gcc
CFLAGS=-std=c99 -O2 -I. -Wall -Wextra

scheduler: src/main.c build/utility.o build/process.o build/fifo.o
	${CC} ${CFLAGS} $^ -o $@

build/utility.o: src/utility.c
	mkdir -p build/
	${CC} ${CFLAGS} -c $^ -o $@

build/process.o: src/process.c
	${CC} ${CFLAGS} -c $^ -o $@

build/fifo.o: src/fifo.c
	${CC} ${CFLAGS} -c $^ -o $@

build/rr.o: src/rr.c
	${CC} ${CFLAGS} -c $^ -o $@

clean:
	rm -rf scheduler build/

