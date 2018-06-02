#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <netinet/udp.h>
//#include <netinet/ip_var.h> // no file on linux
#include <netinet/udp_var.h>  // must comment something in this file, 
#include <sys/param.h>
#include <sys/sysctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

int
main(int argc, char **argv)
{
	int	mib[4], val;
	size_t	len;

	mib[0] = CTL_NET;
	mib[1] = AF_INET;
	mib[2] = IPPROTO_UDP;
	mib[3] = UDPCTL_CHECKSUM;

	len = sizeof(val);
	sysctl(mib, 4, &val, &len, NULL, 0);
	printf("udp checksum flag: %d\n", val);
	exit(0);
}

