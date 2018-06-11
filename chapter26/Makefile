CC=gcc
CFLAGS=-g
RM=rm

TARGET=figure26_3.o 
TARGET+=figure26_4.o 

all: $(TARGET);

figure26_3.o:figure26_3.c
	$(CC) $^ $(CFLAGS) -c -o $@

figure26_4.o:figure26_4.c
	$(CC) $^ $(CFLAGS) -c -o $@

clean:
	rm -f $(TARGET)
