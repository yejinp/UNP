#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <strings.h>
#include <string.h>

#define	SERV_PORT	5555
#define MAXLINE		1024
void 
dg_cli(FILE *fp, int sockfd, struct sockaddr *pservaddr, socklen_t servlen)
{
	int	n;
	socklen_t 	len;
	char	sendline[MAXLINE], recvline[MAXLINE];
	
	while(fgets(sendline, MAXLINE, fp) != NULL) {
		sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);
		n = recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);
		recvline[n] = 0;
		fputs(recvline, stdout);
	}
}

int main(int argc, char **argv)
{
	int	sockfd;
	struct sockaddr_in servaddr;

	if(argc != 2) {
		printf("usage: %s <IPaddress> \n", argv[0]);
		exit(2);
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);


	dg_cli(stdin, sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

}

