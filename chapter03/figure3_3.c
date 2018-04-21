#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

int
main(int argc, char **argv)
{
	struct sockaddr		sa;

	printf("sizeof(struct sockaddr)=%ld\n", sizeof(struct sockaddr));

}

