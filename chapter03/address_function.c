#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <strings.h>

int
main(int argc, char **argv)
{
	struct in_addr	addr;
	char addstr[16] = {0};

	if(argc != 2) {
		printf("Usage:%s address\n", argv[0]);
		exit(2);
	}
	
	if(inet_aton(argv[1], &addr) == 0) {
		printf("%s illegal address.\n", argv[1]);
	} else {
		printf("address:0X%x\n", addr.s_addr);
	}

	printf("inet_addr(%s)]:0X%x\n", argv[1], inet_addr(argv[1]));

	bzero(&addr, sizeof(addr));
	bzero(addstr, sizeof(addstr));

	if(inet_pton(AF_INET, argv[1], &addr.s_addr) == 1) 
	{
		printf("inet pton:0x%x\n", addr.s_addr);
	} else {
		printf("inet pton [ %s ] error.\n", argv[1]);
	}

	if(inet_ntop(AF_INET, &addr.s_addr, addstr, 16) ) {
		printf("address:%s\n", addstr);
	} else {
		printf("inet ntop error:0x%d\n",addr.s_addr);
	}
	exit(0);
}
