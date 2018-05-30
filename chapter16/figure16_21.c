#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define	SERV_PORT 53

int
main(int argc, char **argv)
{

	int	sockfd;
	struct	linger	ling;
	struct sockaddr_in	servaddr;
	
	if(argc != 2) {
		printf("Usage: %s <IPaddress>\n", argv[0]);
		exit(9);
	}

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

	ling.l_onoff = 1;
	ling.l_linger = 0;
	setsockopt(sockfd, SOL_SOCKET, SO_LINGER, &ling, sizeof(ling));
	close(sockfd);

	exit(0);
}
