#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/un.h>
#include <sys/types.h>      
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>

#define	CONTROL_LEN (sizeof(struct cmsghdr) + sizeof(struct cmsgcred))

ssize_t
read_cred(int fd, void *ptr, size_t nbytes, struct cmsgcred *cmsgcredptr)
{
	struct	msghdr	msg;
	struct	iovec	iov[1];
	char	control[CONTROL_LEN];
	int	n;

	msg.msg_name = NULL;
	msg.msg_namelen = 0;
	iov[0].iov_base = ptr;
	iov[0].iov_len = nbytes;
	msg.msg_iov = iov;
	msg.msg_iovlen = 1;
	msg.msg_control = control;
	msg.msg_controllen = sizeof(control);
	msg.msg_flags = 0;

	if(( n = recvmsg(fd, &msg, 0)) < 0) {
		return n;
	}

	cmsgcredptr->cmcred_ngroups = 0;
	if(cmsgcredptr && msg.msg_controllen > 0) {
		struct	cmsghdr *cmptr = (struct cmsghdr *) control;

		if(cmptr->cmsg_len < CONTROL_LEN) {
			printf("control length = %d\n", cmptr->cmsg_len);
			exit(9);
		}
		if(cmptr->cmsg_level != SOL_SOCKET) {
			printf("control level != SOL_SOCKET\n");
			exit(9);
		}
		if(cmptr->cmsg_type != SCM_CREDS) {
			printf("control type != SCM_CREDS\n");
			exit(9);
		}

		memcpy(cmsgcredptr, CMSG_DATA(cmptr), sizeof(struct cmsgcred));
	}

	return n;
}
