#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>

#define MAXLINE 1024

void
dg_cli(FILE *fp, int sockfd, const struct sockaddr *pservaddr, socklen_t servlen)
{

	int 	n;
	char sendline[MAXLINE], recvline[MAXLINE];
	struct	timeval		tv;

	tv.tv_sec = 5;
	tv.tv_usec = 0;

	setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

	while(fgets(sendline, MAXLINE, fp)) {
		sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);
		n = recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);
		if( n < 0) {
			if(errno == EWOULDBLOCK) {
				fprintf(stderr, "socket timeout\n");
				continue;
			}
		} else {
			printf("recvfrom error.\n");
			exit(8);
		}
		recvline[n] = 0;
		fputs(recvline, stdout);
	}

}
