#include <stdio.h>
#include <stdlib.h>
#include <net/if.h>

int
main(void)
{
	int i;
	struct if_nameindex 	*in;
	if(NULL != (in = if_nameindex())) {
	
		for(i = 0; in[i].if_index; i++) {
			printf("index: %3d, name : %12s\n", in[i].if_index, in[i].if_name);
		}
	
	} else {
		perror("if_nameindex error");
		exit(9);
	}
	exit(0);
}
