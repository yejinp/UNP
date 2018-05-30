#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

#include "figure16_14.h"

#define		MAXLINE		1024

void
home_page(const *host, const char *fname)
{
	int	fd, n;
	char	line[MAXLINE];

	fd = tcp_connect(host, SERV);
	
	n = sprintf(line, sizeof(line), GET_CMD, fname);
	write(fd, line, n);

	for ( ; ; ) {
		if((n = read(fd, line, MAXLINE)) == 0) {
			break;
		}
		printf("read %d bytes of home page\n", n);
	}
	printf("end-of-file on home page\n");
	close(fd);
}

