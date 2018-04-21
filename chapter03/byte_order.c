#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>

int 
main(int argc, char **argv)
{

	uint16_t	si;
	uint32_t	li;

	if(argc != 3) {
		printf("Usage:%s short_ingeter long_integer\n", argv[0]);
		exit(7);
	}

	si = atoi(argv[1]);
	li = atoi(argv[2]);

	printf("htons(%s[%x]): %x\n", argv[1], si, htons(si));
	printf("htonl(%s[%x]): %x\n", argv[2], li, htons(li));
	exit(0);
}
