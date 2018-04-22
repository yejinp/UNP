CC=gcc
RM=rm -f

CFLAG=-g
CCFLAG=-c

OBJECTS=figure4_9.o
OBJECTS=figure4_19.o

TARGET=getpeername
TARGET+=getsockname
TARGET+=figure4_11
TARGET+=figure4_13

all:$(TARGET) $(OBJECTS);

figure4_13:figure4_13.c
	$(CC) $(CFLAG)  $^ -o $@

figure4_11:figure4_11.c
	$(CC) $(CFLAG)  $^ -o $@

getpeername:getpeername.c
	$(CC) $(CFLAG)  $^ -o $@

getsockname:getsockname.c
	$(CC) $(CFLAG)  $^ -o $@

figure4_9.o:figure4_9.c
	$(CC)  $(CCFLAG) $(CFLAG) $^ -o $@

figure4_19.o:figure4_19.c
	$(CC)  $(CCFLAG) $(CFLAG) $^ -o $@

clean:
	$(RM) $(TARGET) $(OBJECTS)
