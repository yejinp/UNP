#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

int
main(int argc, char **argv)
{
	struct sockaddr_storage sstorage;

	printf("sizeof(struct sockaddr_storage)=%ld\n", sizeof(struct sockaddr_storage));

}

