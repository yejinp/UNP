CC=gcc
CFLAGS=-g
RM=rm

TARGET=figure15_2
TARGET+=figure15_3.o
TARGET+=figure15_4.o
TARGET+=figure15_5.o
TARGET+=figure15_6.o
TARGET+=figure15_9
TARGET+=figure15_10.o
TARGET+=figure15_11.o
TARGET+=figure15_12
TARGET+=figure15_13.o
TARGET+=figure15_14.o

all: $(TARGET);

figure15_2:figure15_2.c
	$(CC) $^ $(CFLAGS) -o $@

figure15_3.o:figure15_3.c
	$(CC) $^ $(CFLAGS) -c -o $@

figure15_4.o:figure15_4.c
	$(CC) $^ $(CFLAGS) -c -o $@

figure15_5.o:figure15_5.c
	$(CC) $^ $(CFLAGS) -c -o $@

figure15_6.o:figure15_6.c
	$(CC) $^ $(CFLAGS) -c -o $@

figure15_9:figure15_9.c figure15_10.o figure15_11.o
	$(CC) $^ $(CFLAGS) -o $@

figure15_10.o:figure15_10.c
	$(CC) $^ $(CFLAGS) -c -o $@

figure15_11.o:figure15_11.c
	$(CC) $^ $(CFLAGS) -c -o $@

figure15_12:figure15_12.c figure15_13.o
	$(CC) $^ $(CFLAGS) -o $@

figure15_13.o:figure15_13.c
	$(CC) $^ $(CFLAGS) -c -o $@

figure15_14.o:figure15_14.c
	$(CC) $^ $(CFLAGS) -c -o $@

clean:
	rm -f $(TARGET)
