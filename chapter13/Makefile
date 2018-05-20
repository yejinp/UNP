CC=gcc
CFLAGS=-g
RM=rm

TARGET=figure13_4.o
all: $(TARGET);

figure13_4:figure13_4.o
	$(CC) $^ $(CFLAGS) -c -o $@

clean:
	rm -f $(TARGET) *.o
