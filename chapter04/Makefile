CC=gcc
RM=rm -f

CFLAG=-g
CCFLAG=-c

OBJECTS=figure4_9.o

TARGET=getpeername
TARGET+=getsockname

all:$(TARGET) $(OBJECTS);

getpeername:getpeername.c
	$(CC) $(CFLAG)  $^ -o $@

getsockname:getsockname.c
	$(CC) $(CFLAG)  $^ -o $@

figure4_9.o:figure4_9.c
	$(CC)  $(CCFLAG) $(CFLAG) $^ -o $@

clean:
	$(RM) $(TARGET) $(OBJECTS)
