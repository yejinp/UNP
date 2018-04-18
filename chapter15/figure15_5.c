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

void 
dg_echo(int sockfd, struct sockaddr *pcliaddr, socklen_t clilen)
{
	int	n;
	socklen_t 	len;
	char	msg[MAXLINE];
	len = clilen;

	for( ; ;) {
		n = recvfrom(sockfd, msg, MAXLINE, 0, pcliaddr, &len);
		printf("recvd %d bytes.\n", n);
		n = sendto(sockfd, msg, n, 0, pcliaddr, len);
		printf("sendto %d bytes.\n", n);
	}
}

int main(int argc, char **argv)
{
	int	sockfd;
	struct sockaddr_un servaddr, cliaddr;

	unlink(UNIXSTR_PATH);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sun_family = AF_LOCAL;
	strcpy(servaddr.sun_path, UNIXSTR_PATH);

	sockfd = socket(AF_LOCAL, SOCK_DGRAM, 0);
	if(sockfd < 0) {
		perror("socket failed");
		exit(9);
	}
	if(0 > bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr))) {
		perror("bind failed");
		exit(8);
	}

	dg_echo(sockfd, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
}

