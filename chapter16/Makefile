CC=gcc
CFLAGS=-g
RM=rm

TARGET=figure16_3.o
TARGET+=figure16_6.o
all: $(TARGET);

figure16_3:figure16_3.o
	$(CC) $^ $(CFLAGS) -o $@

figure16_6:figure16_6.o
	$(CC) $^ $(CFLAGS) -o $@

clean:
	rm -f $(TARGET) *.o
