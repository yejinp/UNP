#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <limits.h>
#include <arpa/inet.h>
#include <strings.h>

#define		MAXLEN		512

int
main(int argc, char *argv[])
{
	int	sockfd,	n;
	char	recvline[MAXLEN + 1];
	struct	sockaddr_in	servaddr;

	if(argc != 2)
	{
		printf("%s: a.out <IPaddress> \n", argv[0]);
		exit(6);
	}

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("socket error.\n");
		exit(9);
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(13);

	if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0) {
		printf("inet pton error for %s\n", argv[1]);
		exit(errno);
	}

	if(connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
		printf("connect error.\n");
		exit(errno);
	}

	while((n = read(sockfd, recvline, MAXLEN)) > 0) {
		recvline[n] = 0;
		if(fputs(recvline, stdout) == EOF) {
			printf("fputs error\n");
			exit(errno);
		}
	}

	if(n < 0) {
		printf("read error.\n");
		exit(errno);
	}

	exit(0);


}
