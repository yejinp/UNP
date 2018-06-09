#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <signal.h>
#include <string.h>

#define MAXLINE 1024

extern char *sock_ntop_host(struct sockaddr *, socklen_t);

static void recvfrom_alarm(int);
static int pipefd[2];

void
dg_cli(FILE *fp, int sockfd, const struct sockaddr * pservaddr, socklen_t servlen)
{
	int	n, maxfdp1 = sockfd + 1;
	const	int on = 1;
	char	sendline[MAXLINE], recvline[MAXLINE + 1];
	socklen_t	len;
	struct	sockaddr *preply_addr;
	fd_set rset;

	preply_addr = malloc(servlen);
	pipe(pipefd);

	if(sockfd < pipefd[0]) 
		maxfdp1 = pipefd[0] + 1;

	setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on));

	FD_ZERO(&rset);
	signal(SIGALRM, recvfrom_alarm);
	while( fgets(sendline, MAXLINE, fp) != NULL) {
		sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);
		alarm(5);
		
		for ( ; ; ) {

			FD_SET(sockfd, &rset);
			FD_SET(pipefd[0], &rset);
			if((n = select(maxfdp1, &rset, NULL, NULL, NULL)) < 0) {
				if(errno == EINTR) 
					continue;
				else {
					perror("select error");
					exit(9);
				}
				
			}
			if(FD_ISSET(sockfd, &rset)) {
				len = servlen;
				n = recvfrom ( sockfd, recvline, MAXLINE, 0, preply_addr, &len);
				recvline[n] = 0;
				printf("from %s: %s", sock_ntop_host(preply_addr, len), recvline);
			}

			if(FD_ISSET(pipefd[0], &rset)) {
				read(pipefd[0], &n, 1);
				break;
			}
		}
	}

	free(preply_addr);
}


static void
recvfrom_alarm(int signo)
{

	return;
}
