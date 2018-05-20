#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>

int
udp_server(const char *host, const char *serv, socklen_t *addrlen)
{

	int	sockfd, n;
	struct	addrinfo	hints, *res, *ressave;

	bzero(&hints, sizeof(hints));

	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;

	if((n = getaddrinfo(host, serv, &hints, &res)) != 0) {
		printf("udp server error for %s, %s: %s\n", host, serv, gai_strerror(n));
		exit(n);
	}

	ressave = res;

	do {
		sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		if(sockfd < 0) 
			continue;
		if(bind(sockfd, res->ai_addr, res->ai_addrlen) == 0) {
			break;
		}
		close(sockfd);
	} while (( res = res->ai_next));

	if(res == NULL) {
		printf("udp server error for %s, %s\n", host, serv);
		exit(9);
	}

	freeaddrinfo(ressave);
	return (sockfd);
}
