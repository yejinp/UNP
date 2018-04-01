#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <errno.h>
#include <time.h>
#include <arpa/inet.h>
#include <string.h>

#define	MAXLEN 	512

int
main(int argc, char **argv)
{
	int	listenfd, connfd;
	struct	sockaddr_in	servaddr;
	char	buff[MAXLEN];
	time_t	ticks;
	
	listenfd = socket(AF_INET, SOCK_STREAM, 0);

	if(listenfd < 0) {
		printf("socket error.\n");
		exit(9);
	}

	bzero(&servaddr, sizeof(&servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(13);

	if(bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr) ) < 0) {
		printf("bind error.\n");
		return 7;
	}

	if(listen(listenfd, 5) < 0) {
		printf("listen failed.\n");
		return (6);
	}

	for (; ;) {
		connfd = accept(listenfd, (struct sockaddr *) NULL, NULL);
		if(connfd < 0) {
			printf("accept failed.\n");
			exit(9);
		}

		ticks = time(NULL);
		snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
		write(connfd, buff, strlen(buff));

		close(connfd);
	
	}

}
