CC=gcc
CFLAGS=-g

OBJECTS=figure3_12.o
OBJECTS+=figure3_15.o
OBJECTS+=figure3_16.o
OBJECTS+=figure3_17.o
OBJECTS+=figure3_18.o

TARGET=figure3_1 figure3_3 figure3_4 figure3_5 figure3_10 byte_order byte_operation address_function
TARGET=figure3_1
TARGET+=figure3_3
TARGET+=figure3_4
TARGET+=figure3_5
TARGET+=figure3_10
TARGET+=figure3_13
TARGET+=byte_order
TARGET+=byte_operation
TARGET+=address_function

all:$(TARGET) $(OBJECTS);

figure3_15.o:figure3_15.c
	$(CC) $(CFLAGS) -c -o $@ $^

figure3_12.o:figure3_12.c
	$(CC) $(CFLAGS) -c -o $@ $^

figure3_16.o:figure3_16.c
	$(CC) $(CFLAGS) -c -o $@ $^

figure3_17.o:figure3_17.c
	$(CC) $(CFLAGS) -c -o $@ $^

figure3_18.o:figure3_18.c
	$(CC) $(CFLAGS) -c -o $@ $^

address_function: address_function.o
	$(CC) $(CFLAGS) -o $@ $^

byte_operation: byte_operation.o
	$(CC) $(CFLAGS) -o $@ $^

byte_order: byte_order.o
	$(CC) $(CFLAGS) -o $@ $^

figure3_1:figure3_1.o
	$(CC) $(CFLAGS) -o $@ $^

figure3_3:figure3_3.o
	$(CC) $(CFLAGS) -o $@ $^

figure3_4:figure3_4.o
	$(CC) $(CFLAGS) -o $@ $^

figure3_5:figure3_5.o
	$(CC) $(CFLAGS) -o $@ $^

figure3_10:figure3_10.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TARGET) *.o
