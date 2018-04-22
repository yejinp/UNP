CC=gcc
CFLAGS=-g
RM=rm -f

OBJECTS=

TARGET=figure5_2

all:$(TARGET);

figure5_2:figure5_2.o
	$(CC) $^ -o $@

clean:
	$(RM) $(TARGET) $(OBJECTS) *.o
