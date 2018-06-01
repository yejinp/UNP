#include <stdio.h>
#include <stdlib.h>
#include <net/if.h>

int 
main(int argc, char **argv)
{
	int i = 0, idx;

	if(argc < 2) {
		printf("usage: %s <ifnames...>\n", argv[0]);
		exit(9);
	}

	for(i = 1; argv[i]; i++) {
		if(0 == (idx = if_nametoindex(argv[i]))) {
			printf("get index of if [ %s ] failed\n", argv[i]);
		} else {
			printf("%s [%d]\n", argv[i], idx);
		}
	}
	return 0;
}

