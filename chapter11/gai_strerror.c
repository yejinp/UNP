#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>

int
main(void)
{
	printf("EAI_AGAIN: %s\n", gai_strerror(EAI_AGAIN));
	exit(0);
}
