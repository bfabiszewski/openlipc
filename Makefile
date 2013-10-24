CC=gcc
CFLAGS=-I. -Wall -O2
LIB_LIPC=-llipc

all: openlipc-get openlipc-set openlipc-send

openlipc-get: 
	$(CC) $(CFLAGS) $(LIB_LIPC) openlipc-get.c -o openlipc-get

openlipc-set: 
	$(CC) $(CFLAGS) $(LIB_LIPC) openlipc-set.c -o openlipc-set

openlipc-send: 
	$(CC) $(CFLAGS) $(LIB_LIPC) openlipc-send.c -o openlipc-send

.PHONY : clean
clean:
	rm -rf openlipc-get openlipc-set openlipc-send
