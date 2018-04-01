#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

int Socket(int family, int type, int protocol)
{
	int n;
	if((n = socket(family, type, protocol)) < 0) {
		printf("socket error.\n");
		exit(5);
	}

	return (n);
}
