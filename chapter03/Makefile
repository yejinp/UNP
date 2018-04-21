CC=gcc
CFLAGS=-g

TARGET=figure3_1 figure3_3 figure3_4 figure3_5 figure3_10
all:$(TARGET);

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
