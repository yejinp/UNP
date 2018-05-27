#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/un.h>
#include <sys/types.h>      
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

ssize_t 
read_fd(int fd, void *ptr, size_t nbytes, int *recvfd)
{
	struct msghdr	msg;
	struct iovec 	iov[1];

	size_t	n;

//#ifdef	HAVA_MSGHDR_MSG_CONTROL
#if 1
	union {
		struct	cmsghdr	cm;
		char	control[CMSG_SPACE(sizeof(int))];
	}control_un;
	struct	cmsghdr	*cmptr;
	msg.msg_control	= control_un.control;
	msg.msg_controllen = sizeof(control_un.control);
#else

	int	newfd;
	msg.msg_accrights = (caddr_t) &newfd;
	msg.msg_accrightslen = sizeof(int);
#endif

	msg.msg_name = NULL;
	msg.msg_namelen = 0;
	
	iov[0].iov_base = ptr;
	iov[0].iov_len = nbytes;
	
	msg.msg_iov = iov;
	msg.msg_iovlen = 1;

	if(( n = recvmsg(fd, &msg, 0)) <= 0) {
		return (n);
	}

//#ifdef HAVA_MSGHDR_MSG_CONTROL
#if 1
	if((cmptr = CMSG_FIRSTHDR(&msg)) != NULL &&
	   cmptr->cmsg_len == CMSG_LEN(sizeof(int))) {
		if(cmptr->cmsg_level != SOL_SOCKET) {
			printf("control level != SOL_SOCKET\n");
			exit(9);
		}
		if(cmptr->cmsg_type != SCM_RIGHTS) {
			printf("control type != SCM_RIGHTS\n");	
			exit(9);
		}

		*recvfd = *((int *) CMSG_DATA(cmptr));
	} else {
		*recvfd = -1;
	}
#else 
	if(msg.msg_accrightslen == sizeof(int)) {
		*recvfd = newfd;
	} else {
		*recvfd = -1;
	}
#endif

	return n;
}
