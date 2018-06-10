#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <net/if.h>
#include <linux/in.h>
#include <strings.h>
#include <string.h>

#define 	SAP_NAME	"sap.mcast.net"
#define		SAP_PORT	"9875"

void loop(int, socklen_t);

int
main(int argc, char **argv)
{
	int	sockfd;
	const	int	on = 1;
	socklen_t	salen;
	struct	sockaddr *sa;

	if(argc == 1) {
		sockfd = udp_client(SAP_NAME, SAP_PORT, (void **)&sa, &salen);
	} else if(argc == 4) 
		sockfd = udp_client(argv[1], argv[2], (void **) &sa, &salen);
	else {
		printf("usage: %s <mcast-addr> <port#> <interface-name>\n", argv[0]);
		exit(9);
	}

	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
	bind(sockfd, sa, salen);

	mcast_join(sockfd, sa, salen, (argc == 4) ? argv[3] : NULL, 0);
	
	loop(sockfd, salen);

	exit(0);
}
