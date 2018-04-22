#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <strings.h>
#include <unistd.h>
#include <arpa/inet.h>

#define 	SERV_PORT	(5555)
#define		LISTENQ		(5)

#define		MAXLINE		(1024)

void
str_echo(int sockfd)
{
	ssize_t	n;
	char	buf[MAXLINE];

	again:
	while( (n = read(sockfd, buf, MAXLINE)) > 0) {
		if(write(sockfd, buf, n) < 0) {
			perror("write error");
			exit(9);
		}
	}
	if(n < 0 && errno == EINTR) 
		goto again;
	else if(n < 0) {
		perror("read error");
		exit(8);
	}
}


int
main (int argc, char *argv[])
{

	int	listenfd, connfd;
	pid_t	childpid;
	socklen_t	clilen;
	struct sockaddr_in	cliaddr, servaddr;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if(listenfd < 0) {
		perror("socket error");
		exit(9);
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);

	if(bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
		perror("bind error");
		exit(8);
	}

	if(listen(listenfd, LISTENQ) < 0) {
		perror("listen error");
		exit(7);
	}

	for( ; ; ) {
		clilen = sizeof(cliaddr);
		connfd = accept(listenfd, (struct sockaddr *)& cliaddr, &clilen);
		if(connfd < 0) {
			perror("accept error");
			exit(7);
		}

		if((childpid = fork()) == 0) {
			close(listenfd);
			str_echo(connfd);
			exit(0);
		}

		close(connfd);
	
	}

}
