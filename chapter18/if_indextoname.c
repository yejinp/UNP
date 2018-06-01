#include <stdio.h>
#include <stdlib.h>
#include <net/if.h>

int
main(int argc, char **argv)
{
	int i = 1;
	char name[IFNAMSIZ];

	while(i) {
		if(if_indextoname(i, name)) {
			printf("%3d : %10s\n", i, name);
		} else {
			break;
		}
		i++;
	}

}
