#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>

#define	MAXLINE	1024

extern int udp_client(char *, char *, struct sockaddr **, socklen_t *);

int
main(int argc, char **argv)
{
	int	sockfd, n;
	char	recvline[MAXLINE];
	socklen_t	salen;
	struct	sockaddr	*sa;
	
	if(argc != 3) {
		printf("usage: %s <hostname/IPaddress> <service/port#>\n", argv[0]);
		exit(9);
	}

	sockfd = udp_client(argv[1], argv[2], (struct sockaddr **)&sa, &salen);
//	printf("sendgin to %s\n", sock_ntop_host(sa, salen));

	sendto(sockfd, "", 1, 0, sa, salen);

	n = recvfrom(sockfd, recvline, MAXLINE,	0, NULL, NULL);	
	recvline[n] = 0;
	fputs(recvline, stdout);

	exit(0);
}
