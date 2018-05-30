#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "figure16_14.h"

void
write_get_cmd(struct file *fptr)
{
	int	n;
	char	line[MAXLINE];
	
	n = snprintf(line, sizeof(line), GET_CMD, fptr->f_name);

	write(fptr->f_fd, line, n);

	printf("wrote %d ");


}
