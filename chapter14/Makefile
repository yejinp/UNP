CC=gcc
CFLAGS=-g
RM=rm

TARGET=figure14_1.o
TARGET+=figure14_2.o
TARGET+=figure14_3.o
TARGET+=figure14_4.o
TARGET+=figure14_5.o

all: $(TARGET);

figure14_1.o:figure14_1.c
	$(CC) $^ $(CFLAGS) -c -o $@

figure14_2.o:figure14_2.c
	$(CC) $^ $(CFLAGS) -c -o $@

figure14_3.o:figure14_3.c
	$(CC) $^ $(CFLAGS) -c -o $@

figure14_4.o:figure14_4.c
	$(CC) $^ $(CFLAGS) -c -o $@

figure14_5.o:figure14_5.c
	$(CC) $^ $(CFLAGS) -c -o $@

clean:
	rm -f $(TARGET)
