#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

void byte_operate1()
{
	char a = 'a', b = 'b';
	printf("a=%c, b=%c\n", a, b);
	bzero(&b, 1);
	printf("a=%c, b=%c\n", a, b);
	bcopy(&a, &b, 1);
	printf("a=%c, b=%c\n", a, b);
	printf("bcmp(a, b)=%d\n", bcmp(&a, &b, 1));
}

void byte_operate2()
{
	char a = 'a', b = 'b';
	printf("a=%c, b=%c\n", a, b);
	memset(&b, 'c', 1);
	printf("a=%c, b=%c\n", a, b);
	memcpy(&a, &b, 1);
	printf("a=%c, b=%c\n", a, b);
	printf("bcmp(a, b)=%d\n", memcmp(&a, &b, 1));
}

int
main(int argc, char **argv)
{
	byte_operate1();
	byte_operate2();
}
