#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <signal.h>
#include <string.h>
#include <setjmp.h>

#define MAXLINE 1024

extern char *sock_ntop_host(struct sockaddr *, socklen_t);

static void recvfrom_alarm(int);
static sigjmp_buf jmpbuf;

void
dg_cli(FILE *fp, int sockfd, const struct sockaddr * pservaddr, socklen_t servlen)
{
	int	n;
	const	int on = 1;
	char	sendline[MAXLINE], recvline[MAXLINE + 1];
	socklen_t	len;
	struct	sockaddr *preply_addr;

	preply_addr = malloc(servlen);

	setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on));
	
	signal(SIGALRM, recvfrom_alarm);
	while( fgets(sendline, MAXLINE, fp) != NULL) {
		sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);
		
		alarm(5);
		
		for ( ; ; ) {
			if(sigsetjmp(jmpbuf, 1) != 0)
				break;

			len = servlen;
			n = recvfrom ( sockfd, recvline, MAXLINE, 0, preply_addr, &len);
			recvline[n] = 0;
			printf("from %s: %s", sock_ntop_host(preply_addr, len), recvline);
		}
	}

	free(preply_addr);
}


static void
recvfrom_alarm(int signo)
{
	siglongjmp(jmpbuf, 1);
}
