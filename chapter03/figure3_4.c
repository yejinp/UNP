#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

int
main(int argc, char **argv)
{
	struct sockaddr_in6		sa6;

	printf("sizeof(struct sockaddr_in6)=%ld\n", sizeof(struct sockaddr_in6));

}

