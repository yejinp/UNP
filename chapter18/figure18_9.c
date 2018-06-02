#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <net/route.h>
#include <sys/types.h>
#include <linux/rtnetlink.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define	ROUNDUP(a,size) (((a) & ((size) - 1)) ? (1 + ((a) | ((size) - 1))) : (a))

#define	NEXT_SA(ap) (ap = (struct sockaddr *)\
	((caddr_t) ap + (sizeof(ap) ? ROUNDUP(sizeof(ap), sizeof(u_long)):sizeof(u_long))))

void
get_rtaddrs(int addrs, struct sockaddr *sa, struct sockaddr **rti_info)
{
	int	i;
	
	for(i = 0; i < RTAX_MAX; i++) {
		if(addrs & (1 << i)) {
			rti_info[i] = sa;
			NEXT_SA(sa);
		} else 
			rti_info[i] = NULL;
	}
}
