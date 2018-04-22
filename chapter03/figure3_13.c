#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>

const char *
my_inet_ntop(int family, const void *addrptr, char *strptr, size_t len)
{
	const u_char *p = (const u_char *)addrptr;

	if(family == AF_INET) {
		char 	temp[INET_ADDRSTRLEN];
		snprintf(temp, sizeof(temp), "%d.%d.%d.%d",p[0], p[1], p[2], p[3]);
		if(strlen(temp) >= len) {
			errno = ENOSPC;
			return NULL;
		}
		strcpy(strptr, temp);
		return (strptr);

	}

	errno = EAFNOSUPPORT;
	return (NULL);
}

int main(int argc, char **argv)
{
	struct in_addr	ina;
	char  ips[16] = {0};

	bzero(&ina, sizeof(ina));
	if(2 != argc) {
		printf("Usage:%s <address>", argv[0]);
		exit(9);
	}

	if(inet_aton(argv[1], &ina) == 0) {
		printf("address %s illegal.\n", argv[1]);
		exit(8);
	}

	if(my_inet_ntop(AF_INET, &ina, ips, 16)) {
		printf("address: %s\n", ips);
	}

	exit(6);
}
