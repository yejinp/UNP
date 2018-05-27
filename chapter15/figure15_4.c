#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <strings.h>
#include <string.h>
#include <sys/un.h>

#define UNIXSTR_PATH	"/tmp/test_path"
#define MAXLINE		1024

extern void str_cli(FILE *FP, int fd);

int
main(int argc, char **argv) 
{
	int	sockfd;
	struct  sockaddr_un	servaddr;
	
	sockfd = socket(AF_LOCAL, SOCK_STREAM, 0);
	if(sockfd < 0) {
		perror("socket error");
		exit(9);
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sun_family = AF_LOCAL;
	strcpy(servaddr.sun_path, UNIXSTR_PATH);

	connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	
	str_cli(stdin, sockfd);
	exit(0);
}
