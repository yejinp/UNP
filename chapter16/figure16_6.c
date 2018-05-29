#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <errno.h>
#include <string.h>

char *
gf_time(void)
{

	struct	timeval	tv;
	static char str[30];
	char	*ptr;

	if(gettimeofday(&tv, NULL) < 0) {
		perror("gettimeofday error");
		exit(9);
	}
	
	ptr = ctime(&tv.tv_sec);
	strcpy(str, &ptr[11]);

	snprintf(str + 8, sizeof(str) - 8, ".%06ld", tv.tv_usec);
	return (str);
}
