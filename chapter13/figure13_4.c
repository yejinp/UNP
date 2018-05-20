#include <signal.h>
#include <unistd.h>
#include <syslog.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define 	MAXFD	64

extern int daemon_proc;

int 
daemon_init(const char *pname, int facility)
{
	int	i;
	pid_t	pid;

	if(( pid = fork()) < 0) {
		return -1;
	} else if(pid) 
		_exit(0);

	if(setsid() < 0) 
		return -1;

	signal(SIGHUP, SIG_IGN);

	if((pid = fork()) < 0) 
		return -1;
	else if(pid)
		_exit(0);

	daemon_proc = 1;
	chdir("/");
	for(i = 0; i < MAXFD; i++)
		close(i);

	open("/dev/null", O_RDONLY);
	open("/dev/null", O_RDWR);
	open("/dev/null", O_RDWR);

	openlog(pname, LOG_PID, facility);
	return 0;
}
