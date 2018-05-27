#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define	BUFFSIZE	1024
	
int my_open(const char *, int);

int
main(int argc, char **argv)
{
	int	fd, n;
	char	buff[BUFFSIZE];

	if(argc != 2) {
		printf("usage: %s <pathname>\n", argv[0]);
		exit(1);
	}

	if((fd = my_open(argv[1], O_RDONLY)) < 0) {
		printf("cannot open %s\n", argv[1]);
		exit(1);
	}

	while( (n = read(fd, buff, BUFFSIZE) ) > 0) {
		write(STDOUT_FILENO, buff, n);
	}

	exit(0);
}
