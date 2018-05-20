#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>

#define	MAXLINE	1024

extern int tcp_connect(char *, char *);

int
main(int argc, char **argv)
{
	int	sockfd, n;
	char	recvline[MAXLINE + 1];
	socklen_t	len;
	struct sockaddr_storage ss;

	if(argc != 3) {
		printf("Usage %s <hostname/IPaddress> <service/port#>\n", argv[0]);
		exit(8);
	}

	sockfd = tcp_connect(argv[1], argv[2]);

	len = sizeof(ss);
	getpeername(sockfd, (struct sockaddr*)&ss, &len);
	//printf("connected to %s\n", sock_ntop_host((struct sockaddr *)&ss, len));
	while( (n =read(sockfd, recvline, MAXLINE)) > 0) {
		recvline[n] = 0;
		fputs(recvline, stdout);
	}
	exit(0);
}
