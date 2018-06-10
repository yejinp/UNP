#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <net/if.h>
#include <linux/in.h>
#include <strings.h>
#include <string.h>

#define	BUFFSIZE	1024

void
loop(int sockfd, socklen_t	salen)
{

	socklen_t len;
	ssize_t	n;
	char	*p;
	struct	sockaddr *sa;
	struct	sap_packet {
		uint32_t	sap_header;
		uint32_t	sap_src;
		char		sap_data[BUFFSIZE];
	} buf;

	sa = malloc(salen);

	for( ; ; ) {
		len = salen;

		n = recvfrom(sockfd, &buf, sizeof(buf) -1, 0, sa, &len);
		((char *) &buf)[n] = 0;
		buf.sap_header = ntohl(buf.sap_header);

		printf("From %s hash 0x%04x\n", sock_ntop(sa, len),
			buf.sap_header & SAP_HASH_MASK);

		if(((buf.sap_header & SAP_VERSION_MASK) >> SAP_VERSION_SHIFT) > 1) {
			printf("... version field not 1 (0x%08x)", buf.sap_header);
			continue;
		}

		if(buf.sap_header & SAP_IPV6) {
			printf("... IPv6\n");
			continue;
		}

		if(buf.sap_header & (SAP_DELETE | SAP_ENCRYPTED | SAP_COMPRESSED)) {
			printf("... can't parse this packet type (0x%08x)", buf.sap_header);
			continue;
		}
		p = buf.sap_data + ((buf.sap_header & SAP_AUTHLEN_MASK) >> SAP_AUTHLEN_SHIFT);
		if(strcmp(p, "appliction/sdp") == 0) 
			p += 16;
		printf("%s\n", p);
	}
}
