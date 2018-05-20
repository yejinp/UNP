#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <strings.h>

int
tcp_connect(const char *host, const char *serv)
{
	int	sockfd, n;
	struct  addrinfo	hints, *res, *ressave;

	bzero(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if( (n = getaddrinfo(host, serv, &hints, &res)) != 0) {
		printf("tcp connect error for %s, %s: %s\n", host, serv, gai_strerror(n));
		exit(9);
	}

	ressave = res;

	do { 
		sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		if(sockfd < 0) 
			continue;

		if(connect(sockfd, res->ai_addr, res->ai_addrlen) == 0) 
			break;

		close(sockfd);
	} while(( res = res->ai_next));

	if(res == NULL) {
		printf("tcp connect error for %s, %s\n", host, serv);
		exit(9);
	}

	freeaddrinfo(ressave);
	return sockfd;
}
