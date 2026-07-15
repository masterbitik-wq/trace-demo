CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -std=c11 -O2
TARGET = trace_demo

all: $(TARGET)

$(TARGET): trace_demo.o
	$(CC) $(CFLAGS) -o $@ $^

trace_demo.o: trace_demo.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(TARGET) *.o output.txt

.PHONY: all clean