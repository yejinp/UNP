#include "unpifi.h"

struct	ifi_info *
get_ifi_info(int family, int doaliases)
{

	struct	ifi_info *ifi = NULL, *ifihead = NULL, **ifipnext = NULL;
	int	sockfd, len, lastlen, flags, myflags, idx = 0, hlen = 0;
	char	*ptr, *buf, lastname[IFNAMSIZ], *cptr, *haddr, *sdlname;
	struct	ifconf	ifc;
	struct	ifreq	*ifr, ifrcopy;
	struct	sockaddr_in	*sinptr;
	struct	sockaddr_in6	*sin6ptr;
	
	return ifihead;
}

void
free_ifi_info(struct	ifi_info	*ifhead)
{

	struct	ifi_info	*ifi, *ifinext;

	for( ifi = ifihead; ifi ; ifi = ifinext) {
		if(ifi->ifi_addr) 
			free(ifi->ifi_addr);
		if(ifi->ifi_brdaddr)
			free(ifi->ifi_brdaddr);
		if(ifi->ifi_dstaddr)
			free(ifi->ifi_dstaddr);

		ifinext = ifi->ifi_next;
		free(ifi);
	}
}
