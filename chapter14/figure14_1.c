#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>

static void connect_alarm(int);
typedef void (*sighandler_t) (int);

int
connect_timeo(int sockfd, const struct sockaddr *saptr, socklen_t salen, int nsec)
{
	sighandler_t sigfunc;
	int 	n;
	
	// preserve old handler of signal SIGALARM
	sigfunc = signal(SIGALRM, connect_alarm);
	if(alarm(nsec) != 0) {
		printf("connect time out:alarm was already set");
		exit(9);
	}

	if(( n = connect(sockfd, saptr, salen)) < 0) {
		close(sockfd);
		if(errno == EINTR) {
			errno = ETIMEDOUT;
		}
	}

	// turn off the alarm
	alarm(0);

	// restore previous signal handler
	signal(SIGALRM, sigfunc);

	return (n);
}

int
main()
{
}

void connect_alarm(int signo)
{
	return;
}

