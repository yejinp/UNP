#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <errno.h>

#define	MAXLINE	1024

void
str_cli(FILE *fp, int sockfd)
{
	int	maxfdp1, val, stdineof;
	ssize_t	n, nwritten;
	fd_set	rset, wset;
	char	to[MAXLINE], fr[MAXLINE];
	char 	*toiptr, *tooptr, *friptr, *froptr;
	
	val = fcntl(sockfd, F_GETFL, 0);
	fcntl(sockfd, F_SETGF, val | O_NONBLOCK);

	val = fcntl(STDOUT_FILENO, F_GETFL, 0);
	fcntl(STDOUT_FILENO, F_SETGF, val | O_NONBLOCK);

	val = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETGF, val | O_NONBLOCK);
	
	toiptr = tooptr = 0;
	friptr = froptr = 0;

	maxfdp1 = max(max(STDIN_FILENO, STDOUT_FILENO), sockfd) + 1;
	
	for( ; ;) {
		FD_ZERO(&rset);
		FD_ZERO(&wset);
		if(stdineof == 0 && toiptr < &to[MAXLINE]) {
			FD_SET(STDIN_FILENO, &rset);
		}

		if(friptr < &fr[MAXLINE])
			FD_SET(sockfd, &rset);
		if(tooptr != toiptr) 
			FD_SET(sockfd, &wset);
		if(froptr != friptr) 
			FD_SET(STDOUT_FILENO, &wset);

		select(maxfdp1, &rset, &wset, NULL, NULL);

		if(FD_ISSET(STDIN_FILENO, &rset)) {
			if(( n = read(STDIN_FILENO, toiptr, &to[MAXLINE] - toiptr)) < 0) {
				if(errno != EWOULDBLOCK) {
					perror("read error on stdin\n");
					exit(9);
				}
			} else if(n == 0) {
				fprintf(stderr, "%s: EOF on stdin\n", gf_time());
				stdineof = 1;
				if(tooptr == toiptr) 
					shutdown(sockfd, SHUT_WR);
			} else {
				fprintf(stderr, "%s: read %s bytes from stdin\n". gf_time(), n);
				toiptr += n;
				FD_SET(sockfd, &wset);
			}
		}
	}

	if(FD_ISSET(sockfd, &rset)) {
		if( (n = read(sockfd, friptr, &fr[MAXLINE] - friptr)) < 0) {
			if(errno != EWOULDBLOCK) {
				perror("read error on socket");
				exit(9);
			}
		} else if(n == 0) {
			fprintf(stderr, "%s: EOF on socket\n", gf_time());
			if(stdineof)
				return;
			else {
				printf("str_cli: server terminated promaturely\n");
				exit(9);
			}
		} else {
			fprintf(stderr, "%s: read %d bytes from socket\n",gf_time(), n);
			friptr += n;
			FD_SET(STDOUT_FILENO, &wset);
		}
	}

	if(FD_ISSET(STDOUT_FILENO, &wset) && (( n = friptr - froptr) > 0)) {
		if((nwritten = write(STDOUT_FILENO, froptr, n)) < 0) {
			if(errno != EWOULDBLOCK) {
				perror("write error to stdout");
				exit(9);
			}
		} else {
			fprintf(stderr, "%s : wrote %d bytes to stdout\n", gf_time(), nwritten);
			if(froptr == friptr)
				froptr = friptr = fr;
		}
	
	}

	if(FD_ISSET(sockfd, &wset) && ((n = toiptr - tooptr) > 0)) {
		if(( nwritten = write(sockfd, tooptr, n)) < 0) {
			if(errno != EWOULDBLOCK) {
				perror("write error to socket");
				exit(9);
			}
		} else {
			fprintf(stderr, "%s : wrote %d bytes to socket\n", gf_time(), nwritten);
			tooptr += nwritten;
			if(tooptr == toiptr) {
				toiptr = tooptr = to;
			if(stdineof) 
				shutdown(sockfd, SHUT_WR);
			}
		}
	}
}
