#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define		MAXLINE		1024

extern int udp_server(char *, char *, socklen_t *);

int
main(int argc, char **argv)
{
	int	sockfd;
	ssize_t	n;
	time_t	ticks;
	char	buff[MAXLINE];
	socklen_t	len;
	struct	sockaddr_storage cliaddr;

	if(argc == 2) {
		sockfd = udp_server(NULL, argv[1], NULL);
	} else if(argc == 3) {
		sockfd = udp_server(argv[1], argv[2], NULL);
	} else  {
		printf("usage: %s [ <host> ] <service> or port#>\n", argv[0]);
		exit(9);
	}

	for( ; ; ) {
		len = sizeof(cliaddr);
		n = recvfrom(sockfd, buff, MAXLINE, 0, (struct sockaddr *)&cliaddr, &len);
		// printf("datagram from %s\n", sock_ntop((struct sockaddr *)& cliaddr, len);
		ticks = time(NULL);
		snprintf(buff, sizeof(buff), "%2.4s\r\n", ctime(&ticks));
		sendto(sockfd, buff, strlen(buff), 0 , (struct sockaddr *)&cliaddr, len);
	}
}
