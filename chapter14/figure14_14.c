#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>

#define MAXLINE 1024

void
str_echo(int sockfd)
{
	char	line[MAXLINE];
	FILE	*fpin, *fpout;

	fpin = fdopen(sockfd, "r");
	fpout = fdopen(sockfd, "w");

	while(fgets(line, MAXLINE, fpin)) {
		fputs(line, fpout);
	}
}
