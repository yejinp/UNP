CC=gcc
CFLAGS=-g
RM=rm

TARGET=figure21_10.o 
TARGET+=figure21_13.o 

all: $(TARGET);

figure21_10.o:figure21_10.c
	$(CC) $^ $(CFLAGS) -c -o $@

figure21_13.o:figure21_13.c
	$(CC) $^ $(CFLAGS) -c -o $@

clean:
	rm -f $(TARGET)
