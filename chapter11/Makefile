CC=gcc
CFLAGS=-g
RM=rm

TARGET=figure11_3 
TARGET+=figure11_4
TARGET+=gai_strerror
TARGET+=figure11_9.o
TARGET+=figure11_10.o
TARGET+=figure11_11
TARGET+=figure11_12.o
TARGET+=figure11_13
TARGET+=figure11_14
TARGET+=figure11_15.o
TARGET+=figure11_16
TARGET+=figure11_17.o
TARGET+=figure11_18.o
TARGET+=figure11_19

all: $(TARGET);

figure11_3:figure11_3.c
	$(CC) $^ $(CFLAGS) -o $@

figure11_4:figure11_4.c
	$(CC) $^ $(CFLAGS) -o $@

figure11_9.o:figure11_9.c
	$(CC) $^ $(CFLAGS) -c -o $@

figure11_10.o:figure11_10.c
	$(CC) $^ $(CFLAGS) -c -o $@

figure11_11:figure11_10.o figure11_11.c
	$(CC) $^ $(CFLAGS) -o $@

figure11_12.o:figure11_12.c
	$(CC) $^ $(CFLAGS) -c -o $@

figure11_13:figure11_12.o figure11_13.c
	$(CC) $^ $(CFLAGS) -o $@

figure11_14:figure11_12.o figure11_14.c
	$(CC) $^ $(CFLAGS) -o $@

figure11_15.o:figure11_15.c
	$(CC) $^ $(CFLAGS) -c -o $@

figure11_16:figure11_15.o figure11_16.c
	$(CC) $^ $(CFLAGS) -o $@

figure11_17.o:figure11_17.c
	$(CC) $^ $(CFLAGS) -c -o $@

figure11_18.o:figure11_18.c
	$(CC) $^ $(CFLAGS) -c -o $@

gai_strerror:gai_strerror.c
	$(CC) $^ $(CFLAGS) -o $@

figure11_19:figure11_18.o figure11_19.c
	$(CC) $^ $(CFLAGS) -o $@

clean:
	rm -f $(TARGET)
