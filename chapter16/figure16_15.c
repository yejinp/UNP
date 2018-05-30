#include "figure16_14.h"

#define MAXLINE 1024

int
main(int argc, char **argv)
{
	int	i, fd, n, maxnconn, flags, error;
	char	buf[MAXLINE];
	fd_set	rs, ws;

	if(argc < 5) {
		printf("usage: %s <#conns> <hostname> <homepage> <file1> ...\n", argv[0]);
		exit(5);
	}

	maxnconn = atoi(argv[1]);
	
	nfiles = min(argc - 4, MAXFILES);
	for(i = 0; i < nfiles; i++) {
		file[i].f_name = argv[i + 4];
		file[i].f_host = argv[2];
		file[i].f_flags = 0;
	}

	printf("mfiles = %d\n", argv[3]);

	home_page(argv[2], argv[3]);

	FD_ZERO(&rset);
	FD_ZERO(&wset);

	maxfd = -1;
	nlefttoread = nlefttoconn = nfiles;
	nconn = 0;

}
