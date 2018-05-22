CC=gcc
CFLAGS=-g
RM=rm -f

OBJECTS=figure5_3.o
OBJECTS+=figure5_4.o
OBJECTS+=figure5_5.o
OBJECTS+=figure5_6.o
OBJECTS+=figure5_7.o

TARGET=figure5_2

all:$(TARGET) $(OBJECTS);

figure5_2:figure5_2.c
	$(CC) $^ -o $@

figure5_3.o:figure5_3.c
	$(CC) $^ -c -o $@

figure5_4.o:figure5_4.c figure5_5.o
	$(CC) $^ -c -o $@

figure5_5.o:figure5_5.c
	$(CC) $^ -c -o $@

figure5_6.o:figure5_6.c
	$(CC) $^ -c -o $@

figure5_7.o:figure5_7.c
	$(CC) $^ -c -o $@

clean:
	$(RM) $(TARGET) $(OBJECTS) 
