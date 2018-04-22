#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAXLINE (1024)
#define LISTENQ	(5)

void doit(int connfd) 
{
	char	buff[MAXLINE];
	time_t	ticks;
	ticks = time(NULL);
	snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
	if(write(connfd, buff, strlen(buff)) < 0) {
		perror("write error");
	}
	close(connfd);

}

int
main(int argc, char **argv)
{
	int	listenfd, connfd;
	socklen_t	len;
	struct sockaddr_in servaddr, cliaddr;
	pid_t pid;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if(listenfd < 0 ) {
		perror("socket error");
		exit(9);
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(13);
	
	if(bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
		perror("bind failed");
		exit(6);
	}

	if(listen(listenfd, LISTENQ) < 0) {
		printf("listen error");
		exit(8);
	}

	for( ; ; ) {
		len = sizeof(cliaddr);
		connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &len);
		if(connfd < 0) {
			perror("accept error");
			exit(7);
		}
		if (( pid = fork() == 0)) {
			close(listenfd);
			doit(connfd);
			close(connfd);
			exit(0);
		}
		close(connfd);

	
	}

}
