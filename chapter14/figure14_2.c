#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>

#define MAXLINE	1024

static void sig_alrm(int);

void 
dg_cli(FILE *fp, int sockfd, const struct sockaddr *pservaddr, socklen_t servlen)
{
	int 	n;	
	char	sendline[MAXLINE], recvline[MAXLINE];
	signal(SIGALRM, sig_alrm);

	while(fgets(sendline, MAXLINE, fp) != NULL) {
		sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);

		alarm(5);
		if((n=recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL)) < 0) {
			if(errno == EINTR) {
				fprintf(stderr,"socket timeout\n");
			} else {
				perror("recvfrom error");
				exit(8);
			}
		} else {
			alarm(0);
			recvline[n] = 0;
			fputs(recvline, stdout);
		}
	}
}

static void
sig_alrm(int signo)
{

	return;
}
