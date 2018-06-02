CC=gcc
CFLAGS=-g
RM=rm

TARGET=if_nametoindex
TARGET+=if_indextoname
TARGET+=if_nameindex
TARGET+=figure18_9.o
TARGET+=figure18_13

all: $(TARGET);

if_nametoindex:if_nametoindex.c
	$(CC) $^ $(CFLAGS) -o $@

if_indextoname:if_indextoname.c
	$(CC) $^ $(CFLAGS) -o $@

figure18_9.o:figure18_9.c
	$(CC) $^ $(CFLAGS) -c -o $@

figure18_13:figure18_13.c
	$(CC) $^ $(CFLAGS) -o $@

if_nameindex:if_nameindex.c
	$(CC) $^ $(CFLAGS) -o $@

clean:
	rm -f $(TARGET) 
