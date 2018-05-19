CC=gcc
CFLAGS=-g
RM=rm

TARGET=figure11_3 
TARGET+=figure11_4
all: $(TARGET);

figure11_3:figure11_3.c
	$(CC) $^ $(CFLAGS) -o $@

figure11_4:figure11_4.c
	$(CC) $^ $(CFLAGS) -o $@

clean:
	rm -f $(TARGET)
