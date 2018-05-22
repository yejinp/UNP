#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

void
sig_chld(int signo)
{
	pid_t	pid;
	int	stat;

	pid = wait(&stat);
	printf("child %d terminated\n", pid);
	return;
}
