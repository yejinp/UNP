#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char **argv)
{
	struct in_addr ia;
	struct sockaddr_in sa;

	printf("sizeof(struct in_addr)=%ld\n", sizeof(struct in_addr));
	printf("sizeof(struct sockaddr_in)=%ld\n", sizeof(struct sockaddr_in));

}

