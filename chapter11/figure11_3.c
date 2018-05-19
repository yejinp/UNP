#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <arpa/inet.h>

int
main(int argc, char **argv)
{
	char *ptr, **pptr;
	char str[INET_ADDRSTRLEN];
	struct hostent *hptr;

	while( --argc > 0) {
		ptr = *++argv;
		if( (hptr = gethostbyname(ptr)) == NULL ) {
			printf("gethostbyname error for host %s: %s\n", ptr, hstrerror(h_errno));
			continue;
		}
	
		printf("offical hostname:%s \n", hptr->h_name);

		for(pptr = hptr->h_aliases; *pptr; pptr ++ ) {
			printf("\talias: %s\n", *pptr);
		}

		switch(hptr->h_addrtype) {
			case AF_INET:
				pptr = hptr->h_addr_list;
				for(; *pptr; pptr++) {
					inet_ntop(hptr->h_addrtype, *pptr, str, sizeof(str));
					printf("\taddress: %s\n", str); 
				}
				break;
			default:
				printf("unknown address type\n");
				break;
		}
	}
	exit(0);
}
