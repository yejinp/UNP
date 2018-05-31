#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>

#include "unpifi.h"

int
main(int argc, char **argv)
{
	struct	ifi_info *ifi, *ifihead;
	struct	sockaddr	*sa;
	u_char	*ptr;
	int	i, family, doaliases;

	if(argc != 3) {
		printf("usage: %s <inet4|inet6> <doaliases>\n", argv[0]);
		exit(9);
	}

	if(strcmp(argv[1], "inet4") == 0) 
		family = AF_INET4;
	else if(strcmp(argv[1], "inet6") == 0) 
		family = AF_INET6;
	else {
		printf("invalid <address-family>\n");
		exit(9);
	}

	doaliases = atoi(argv[2]);

	for(ifihead = ifi = Get_ifi_info(family, doaliases);
		ifi ; ifi = ifi->ifi_next) {
		printf("%s: ", ifi->ifi_name);
		if(ifi->ifi_index) {
			printf("(%d) ", ifi->ifi_index);
		}
		printf("<");
		if(ifi->ifi_flags & IFF_UP) 		printf("UP ");
		if(ifi->ifi_flags & IFF_BROADCAST) 	printf("BCAST ");
		if(ifi->ifi_flags & IFF_MULTICAST)	printf("MCAST ");
		if(ifi->ifi_flags & IFF_LOOPBACK)	printf("LOOP ");
		if(ifi->ifi_flags & IFF_POINTOPOINT)	printf("P2P ");
		printf(">");

		if( (i = ifi->ifi_hlen) > 0) {
			ptr = ifi->ifi_haddr;
			do {
				printf("%s%x", (i == ifi->ifi_hlen) ? " " : ":", *ptr++);
			} while(--i > 0)
			printf("\n");
		}

		if(ifi->ifi_mtu) 
			printf(" MTU: %d\n", ifi->ifi_mtu);

		if((sa = ifi->ifi_addr)) {
			printf(" IP addr: %s\n", sock_ntop_host(sa, sizeof(*sa)));
		}

		if((sa = ifi->ifi_brdaddr)) {
			printf(" broadcase addr: %s\n", sock_ntop_host(sa, sizeof(*sa)));

		}
		if((sa = ifi->ifi_dstaddr)) {
			printf(" destination addr: %s\n", sock_ntop_host(sa, sizeof(*sa)));
	}
	free_ifi_info(ifihead);
	exit(0);
}
