#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <strings.h>

#define		MAXLEN  512

int
main(int argc, char **argv)
{
	int	sockfd, n;
	char	recvline[MAXLEN + 1];
	struct	sockaddr_in6	servaddr;
	
	if(argc != 2) {
		printf("usage: a.out <IPaddress>\n");
		return 9;
	}

	if((sockfd = socket(AF_INET6, SOCK_STREAM, 0)) < 0) {
		printf("socket error.\n");
		return 8;
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin6_family = AF_INET6;
	servaddr.sin6_port = htons(13);
	if(inet_pton(AF_INET6, argv[1], &servaddr.sin6_addr) <= 0) {
		printf("inet pton error for %s.\n", argv[1]);
		return 7;
	}

	if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0 ) {
		printf("connect error.\n");
		return 8;
	}

	while((n = read(sockfd, recvline, MAXLEN)) >0 ) {
		recvline[n] = 0;
		if(fputs(recvline, stdout) == EOF) {
			printf("fputs error.\n");
			return 9;
		}
	}

	if(n < 0) {
		printf("read error.\n");
		exit(8);
	}

	exit(0);


}
