CC=gcc
CFLAGS=-g
RM=rm

TARGET=figure14_1.o
TARGET+=figure14_2.o
all: $(TARGET);

figure14_1.o:figure14_1.c
	$(CC) $^ $(CFLAGS) -c -o $@

figure14_2.o:figure14_2.c
	$(CC) $^ $(CFLAGS) -c -o $@

clean:
	rm -f $(TARGET) *.o
