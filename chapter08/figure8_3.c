#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <strings.h>

#define	SERV_PORT	5555
#define MAXLINE		1024
void 
dg_echo (int sockfd, struct sockaddr *pcliaddr, socklen_t clilen)
{
	int	n;
	socklen_t 	len;
	char	msg[MAXLINE];
	
	len = clilen;
	for( ; ; ) {
		n = recvfrom(sockfd, msg, MAXLINE, 0, pcliaddr, &len);

		sendto(sockfd, msg, n, 0, pcliaddr, len);
	}

}

int main(int argc, char **argv)
{
	int	sockfd;
	struct sockaddr_in servaddr, cliaddr;

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);

	bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

	dg_echo(sockfd, (struct sockaddr *)&cliaddr, sizeof(cliaddr));

}

