#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include <errno.h>

#define		SERV_PORT	5555
#define		MAXLINE		1024

extern int readline(int sockfd, char *buf, size_t n);

#if 1
void 
str_cli(FILE *fp, int sockfd)
{
	char	sendline[MAXLINE], recvline[MAXLINE];

	while(fgets(sendline, MAXLINE, fp)) {
		if(write(sockfd, sendline, strlen(sendline)) < 0) {
			perror("write error");
		}

		if(readline(sockfd, recvline, MAXLINE) == 0) {
			printf("server terminated prematurely");
			exit(5);
		}

		fputs(recvline, stdout);
	}
}
#endif 
#if 0
int
main(int argc, char **argv)
{

	int	sockfd;
	struct	sockaddr_in	servaddr;

	if(argc != 2) {
		printf("Usage: %s <IPaddress>\n", argv[0]);
		exit(9);
	}

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0) ) < 0) {
		perror("socket error");
		exit(8);
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr) == 0) {
		printf("IPaddress %s illegal\n", argv[1]);
		exit(7);
	}

	if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
		perror("connect error");
		exit(6);
	}

	str_cli(stdin, sockfd);
	exit(0);
}

#endif
