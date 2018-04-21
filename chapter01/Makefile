CC=gcc
CFLAGS=-g
RM=rm

TARGET=figure1_5 figure1_6 figure1_8.o figure1_9
all: $(TARGET);

figure1_5:figure1_5.o
	$(CC) $^ $(CFLAGS) -o $@
figure1_6:figure1_6.o
	$(CC) $^ $(CFLAGS) -o $@
figure1_8.o: figure1_8.c
	$(CC) $^ -c -o $@  
figure1_9:figure1_9.o
	$(CC) $^ $(CFLAGS) -o $@

clean:
	rm -f $(TARGET) *.o
