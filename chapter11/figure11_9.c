#include <netdb.h>
#include <unistd.h>
#include <strings.h>

struct addrinfo *
host_serv(const char *host, const char *serv, int family, int socktype)
{
	int	n;
	struct	addrinfo hints, *res;

	bzero(&hints, sizeof(hints));
	hints.ai_flags = AI_CANONNAME;
	hints.ai_family = family;
	hints.ai_socktype = socktype;
	if( (n = getaddrinfo(host, serv, &hints, &res)) != 0) {
		return NULL;
	}

	return res;
}
