#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <strings.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <arpa/inet.h>

#define		SERV_PORT	53

extern void str_cli(FILE *fp, int sockfd);

int
main(int argc, char **argv)
{
	int	sockfd;
	struct	sockaddr_in	servaddr;

	if(argc != 2) {
		printf("Usage: %s <IPaddress>\n", argv[0]);
		exit(0);
	}

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{	
		perror("socket error");
		exit(sockfd);
	}


	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr) != 1)
	{
		perror("inetpton error");
		exit(9);
	}

	if(connect(sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr)) < 0) {
		perror("connect error");
		exit(9);
	}

	str_cli(stdin, sockfd);
	exit(0);
}
