#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <net/if.h>
#include <linux/in.h>
#include <strings.h>
#include <string.h>

int
mcast_set_loop(int sockfd, int onoff)
{
	u_char	flag;
	switch (sockfd_to_family(sockfd)) {
	case AF_INET: {
		flag = onoff;
		return setsockopt(sockfd, IPPROTO_IP, IP_MULTICAST_LOOP, 
				&flag, sizeof(flag));
	}
#ifdef IPV6
	case AF_INET6:	{
		flag = onoff;
		return setsockopt(sockfd, IPPROTO_IPv6, IPv6_MULTICAST_LOOP, 
				&flag, sizeof(flag));
		
	}
#endif
	default:
		errno = EAFNOSUPPORT;
		return -1;
	}

}
