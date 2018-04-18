#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <strings.h>
#include <string.h>
#include <sys/un.h>

#define	SERV_PORT	5555
#define UNIXSTR_PATH	"/tmp/test_path"
#define MAXLINE		1024
void 
dg_cli(FILE *fp, int sockfd, struct sockaddr *pservaddr, socklen_t servlen)
{
	int	n;
	socklen_t 	len;
	char	sendline[MAXLINE], recvline[MAXLINE];
	
	while(fgets(sendline, MAXLINE, fp) != NULL) {
		n = sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);
		printf("sendto %d bytes.\n", n);
		n = recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);
		printf("recvd %d bytes.\n", n);
		recvline[n] = 0;
		fputs(recvline, stdout);
	}
}

int main(int argc, char **argv)
{
	int	sockfd;
	struct sockaddr_un servaddr, cliaddr;

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sun_family = AF_LOCAL;
	strcpy(servaddr.sun_path, UNIXSTR_PATH);

	sockfd = socket(AF_LOCAL, SOCK_DGRAM, 0);
	if(sockfd < 0) {
		perror("socket failed");
		exit(9);
	}

	bzero(&cliaddr, sizeof(cliaddr));
	cliaddr.sun_family = AF_LOCAL;
	strcpy(cliaddr.sun_path, tmpnam(NULL));
	if(0 > bind(sockfd, (struct sockaddr *)&cliaddr, sizeof(cliaddr))) {
		perror("bind failed");
		exit(6);
	}

	dg_cli(stdin, sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

}

