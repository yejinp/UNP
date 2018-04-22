#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>

void 
Listen(int fd, int backlog)
{
	char *ptr;

	if((ptr = getenv("LISTENQ"))){
		backlog = atoi(ptr);
	}

	if(listen(fd, backlog) < 0) {
		perror("listen error");
		exit(9);
	}


}
