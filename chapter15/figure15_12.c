#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/un.h>
#include <sys/types.h>      
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

extern ssize_t write_fd(int, char *, ssize_t, int);

int
main(int argc, char **argv)
{
	int	fd;
	if(argc != 4) {
		printf("usage: %s <sockfd#> <filename> <mode>\n", argv[0]);
		exit(9);
	}

	if((fd = open(argv[2], atoi(argv[3]))) < 0) {
		exit((errno > 0) ? errno :255);
	}

	if(write_fd(atoi(argv[1]), "", 1, fd) < 0) {
		exit((errno > 0) ? errno :255);
	}
	exit(0);
}
