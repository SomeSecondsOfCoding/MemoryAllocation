CC = gcc
CFLAGS = -std=c99 -pedantic -Wall -Wextra -g
TARGET = bin/memory

OBJS = build/main.o build/memory.o

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

src/main.o: src/main.c src/memory.h
	$(CC) $(CFLAGS) -c src/main.c -o src/main.o

src/memory.o: src/memory.c src/memory.h
	$(CC) $(CFLAGS) -c src/memory.c -o src/memory.o

clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean