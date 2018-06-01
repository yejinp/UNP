CC=gcc
CFLAGS=-g
RM=rm

TARGET=if_nametoindex
TARGET+=if_indextoname
TARGET+=if_nameindex

all: $(TARGET);

if_nametoindex:if_nametoindex.c
	$(CC) $^ $(CFLAGS) -o $@

if_indextoname:if_indextoname.c
	$(CC) $^ $(CFLAGS) -o $@

if_nameindex:if_nameindex.c
	$(CC) $^ $(CFLAGS) -o $@

clean:
	rm -f $(TARGET) 
