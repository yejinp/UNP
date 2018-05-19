#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include <string.h>


#define MAXLINE	1024

int
main(int argc, char **argv)
{
	int	sockfd, n;
	char	recvline[MAXLINE + 1];
	struct sockaddr_in	servaddr;
	struct in_addr	**pptr;
	struct in_addr  *inetaddrp[2];
	struct in_addr  inetaddr;
	struct hostent *hp;
	struct servent *sp;

	if(argc != 3) {
		printf("usage: %s <hostname> <serviec>\n", argv[0]);
		exit(9);
	}

	if( (hp = gethostbyname(argv[1])) == NULL ) {
		if(inet_aton(argv[1], &inetaddr) == 0) {
			printf("hostname error for %s: %s\n", argv[1], hstrerror(h_errno));
			exit(9);
		} else {
			inetaddrp[0] = &inetaddr;
			inetaddrp[1] = NULL;
			pptr = inetaddrp;
		}
	} else {
		pptr = (struct in_addr **) hp->h_addr_list;
	}

	if((sp = getservbyname(argv[2], "tcp")) == NULL) {
		printf("getservbyname error for %s\n", argv[2]);
		exit(9);
	}

	for( ; *pptr; pptr++) {
		sockfd = socket(AF_INET, SOCK_STREAM, 0);

		bzero(&servaddr, sizeof(servaddr));
		servaddr.sin_family = AF_INET;
		servaddr.sin_port = sp->s_port;
		memcpy(&servaddr.sin_addr, *pptr, sizeof(struct in_addr));
		//printf("trying %s\n", sock_ntop((struct sockaddr *) &servaddr, sizeof(servaddr)));
		if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == 0)
			break;

		printf("connect error\n");
		close(sockfd);
	}

	if(*pptr == NULL) {
		printf("unable to connect\n");
		exit(9);
	}

	while(( n = read(sockfd, recvline, MAXLINE)) > 0) {
		recvline[n] = 0;
		fputs(recvline, stdout);
	}

	exit(0);
}
