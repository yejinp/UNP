#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/un.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <signal.h>

#define UNIXSTR_PATH  "/chapter15.sock"
#define LISTENQ  5

extern void str_echo(int);

int
main(int argc, char **argv)
{
	int	listenfd, connfd;
	pid_t	childpid;
	socklen_t	chilen;
	struct sockaddr_un	cliaddr, servaddr;
	void sig_chld(int);

	listenfd = socket(AF_LOCAL, SOCK_STREAM, 0);
	if(listenfd < 0) {
		perror("socket error");
		exit(9);
	}

	unlink(UNIXSTR_PATH);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sun_family = AF_LOCAL;	
	strcpy(servaddr.sun_path, UNIXSTR_PATH);

	if(bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
		perror("bind error");
		exit(9);
	}

	if(listen(listenfd, LISTENQ) < 0) {
		perror("listen error");
		exit(9);
	}

	signal(SIGCHLD, sig_chld);

	for( ; ;) {
		chilen = sizeof(cliaddr);
		if( (connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &chilen)) < 0) {
			if(errno == EINTR) 
				continue;
			else {
				perror("accept error");
				exit(9);
			}
		}

		if((childpid == fork()) == 0) {
			close(listenfd);
			str_echo(connfd);
			exit(0);
		}

		close(connfd);
	}
}
