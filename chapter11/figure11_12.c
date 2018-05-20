#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <strings.h>
#include <unistd.h>

#define LISTENQ  5

int
tcp_listen(const char *host, const char *serv, socklen_t *addrlenp)
{

	int	listenfd, n;
	const int on = 1;
	struct addrinfo hints, *res, *ressave;
	
	bzero(&hints, sizeof(struct addrinfo));
	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if((n = getaddrinfo(host, serv, &hints, &res)) != 0) {
		printf("tcp listen error for %s, %s: %s\n", host, serv, gai_strerror(n));
		exit(n);
	}

	ressave = res;

	do {
		listenfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		if(listenfd < 0 ) {
			continue;
		}

		setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

		if(bind(listenfd, res->ai_addr, res->ai_addrlen) == 0) {
			break;
		}

		close(listenfd);
	} while (( res = res->ai_next));

	if(res == NULL) {
		printf("tcp listen error for %s, %s\n", host, serv);
		exit(9);
	}

	if(listen(listenfd, LISTENQ) < 0) {
		printf("listen error for %s, %s\n", host, serv);
		exit(9);
	}

	if(addrlenp)
		*addrlenp = res->ai_addrlen;

	freeaddrinfo(ressave);
	return listenfd;
}
