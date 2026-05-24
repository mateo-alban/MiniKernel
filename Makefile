CC=gcc

CFLAGS=-Wall -pthread -Iinclude

SRC=src/main.c src/queue.c src/cpu.c

TARGET=minikernel

all:
	$(CC) $(SRC) $(CFLAGS) -o $(TARGET)