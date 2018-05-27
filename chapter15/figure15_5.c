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

extern void dg_echo(int, struct sockaddr *, socklen_t);

int
main(int argc, char **argv) 
{
	int	sockfd;
	struct  sockaddr_un	servaddr, cliaddr;
	
	sockfd = socket(AF_LOCAL, SOCK_DGRAM, 0);
	if(sockfd < 0) {
		perror("socket error");
		exit(9);
	}

	unlink(UNIXSTR_PATH);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sun_family = AF_LOCAL;
	strcpy(servaddr.sun_path, UNIXSTR_PATH);

	bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	
	dg_echo(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
}
