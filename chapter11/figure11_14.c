#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#define	MAXLINE	1024

extern int tcp_listen(char *, char *, socklen_t *);

int
main(int argc, char **argv)
{
	int	listenfd, connfd;
	socklen_t	len, addrlen;
	char 	buff[MAXLINE];
	time_t	ticks;
	struct sockaddr_storage cliaddr;

	if(argc == 2) {
		listenfd = tcp_listen(NULL, argv[1], &addrlen);
	} else if(argc == 3) {
		listenfd = tcp_listen(NULL, argv[1], &addrlen);
	} else {
		printf("usage: %s < [host] > <service or port#>\n", argv[0]);
		exit(9);
	}

	for( ; ; ) {
		len = sizeof(cliaddr);
		connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &len);
		// printf("connection from %s\n", sock_ntop((struct sockaddr *)&cliaddr, len);
		
		ticks = time(NULL);
		snprintf(buff, sizeof(buff), "%2.4s", ctime(&ticks));
		write(connfd, buff, strlen(buff));
		close(connfd);
	}

}
