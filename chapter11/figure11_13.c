#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <strings.h>
#include <string.h>

#define		MAXLINE		1024

extern int tcp_listen(char *, char *, socklen_t *);

int
main(int argc, char **argv)
{
	int	listenfd, connfd;
	socklen_t	len;
	char	buf[MAXLINE];
	time_t	ticks;
	struct sockaddr_storage  cliaddr;

	if(argc != 2) {
		printf("usage:%s <service or port#>\n", argv[0]);
		exit(9);
	}

	listenfd = tcp_listen(NULL, argv[1], NULL);
	
	for( ; ;) {
		len = sizeof(cliaddr);
		connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &len);
		//printf("connection from %s\n", sock_ntop((struct sockaddr *)&cliaddr, len));
		ticks = time(NULL);
		snprintf(buf, sizeof(buf), "%2.4s\r\n", ctime(&ticks));
		write(connfd, buf, strlen(buf));
		close(connfd);
	}
}

