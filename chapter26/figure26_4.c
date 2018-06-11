#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

static void *doit(void *);

int
main(int argc, char **argv)
{
	int	listenfd, connfd, *iptr;
	pthread_t	tid;
	socklen_t	addrlen, len;
	struct sockaddr *cliaddr;

	if(argc == 2) 
		listenfd = tcp_listen(NULL, argv[1], &addrlen);
	else if(argc == 3) 
		listenfd = tcp_listen(argv[1], argv[2], &addrlen);
	else {
		printf("usage: %s  [ <host> ] <service or port>\n", argv[0]);
		exit(9);
	}

	cliaddr = malloc(addrlen);

	for( ; ;) {
		len = addrlen;
		iptr = malloc(sizeof(int));
		*iptr = accept(listenfd, cliaddr, &len);
		pthread_create(&tid, NULL, &doit, iptr);
	}
}


static void *
doit(void *arg)
{
	int	connfd;
	connfd = *((int *)arg);
	free(arg);
	pthread_detach(pthread_self());
	str_echo(connfd);
	close(connfd);
	return NULL;

}
