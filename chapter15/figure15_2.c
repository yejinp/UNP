#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <strings.h>
#include <string.h>
#include <sys/un.h>


int main(int argc, char **argv)
{
	int	sockfd;
	socklen_t	len;
	struct sockaddr_un addr1, addr2;

	if(argc != 2) {
		printf("usage: %s <pathname>\n", argv[0]);
		exit(8);
	}

	unlink(argv[1]);
	bzero(&addr1, sizeof(addr1));
	addr1.sun_family = AF_LOCAL;
	strncpy(addr1.sun_path, argv[1], sizeof(addr1.sun_path) - 1);

	sockfd = socket(AF_LOCAL, SOCK_DGRAM, 0);
	if(sockfd < 0) {
		perror("socket failed");
		exit(9);
	}
	if(0 > bind(sockfd, (struct sockaddr*)&addr1, sizeof(addr1))) {
		perror("bind failed");
		exit(8);
	}

	len = sizeof(addr2);
	if(getsockname(sockfd, (struct sockaddr*) &addr2, &len) < 0) {
		perror("get sock name failed");
		exit(9);
	}

	printf("bound name = %s, returned len = %d\n", addr2.sun_path, len);
	exit(0);
}

