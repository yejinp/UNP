CC=gcc
CFLAGS=-g
RM=rm

TARGET=figure20_5.o 
TARGET+=figure20_6.o 
TARGET+=figure20_7.o 
TARGET+=figure20_8.o 
TARGET+=figure20_9.o 
TARGET+=figure20_10.o 

all: $(TARGET);

figure20_5.o:figure20_5.c
	$(CC) $^ $(CFLAGS) -c -o $@

figure20_6.o:figure20_6.c
	$(CC) $^ $(CFLAGS) -c -o $@

figure20_7.o:figure20_7.c
	$(CC) $^ $(CFLAGS) -c -o $@

figure20_8.o:figure20_8.c
	$(CC) $^ $(CFLAGS) -c -o $@

figure20_9.o:figure20_9.c
	$(CC) $^ $(CFLAGS) -c -o $@

figure20_10.o:figure20_10.c
	$(CC) $^ $(CFLAGS) -c -o $@

clean:
	rm -f $(TARGET)
