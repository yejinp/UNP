CC=gcc
CFLAGS=-g
RM=rm

TARGET=figure16_3.o
TARGET+=figure16_6.o
TARGET+=figure16_11.o
TARGET+=figure16_21.o

all: $(TARGET);

figure16_3.o:figure16_3.c
	$(CC) $^ $(CFLAGS) -c -o $@

figure16_6.o:figure16_6.c
	$(CC) $^ $(CFLAGS) -c -o $@

figure16_11.o:figure16_11.c
	$(CC) $^ $(CFLAGS) -c -o $@

figure16_21.o:figure16_21.c
	$(CC) $^ $(CFLAGS) -c -o $@

clean:
	rm -f $(TARGET) *.o
