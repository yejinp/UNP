#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <errno.h>

int
main()
{
	struct	sockaddr	laddr;
	socklen_t	slen;
	if(0 > getpeername(STDIN_FILENO, &laddr, &slen))
		perror("getpeername failed");

}
