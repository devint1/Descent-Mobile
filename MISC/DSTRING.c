#include <ctype.h>

#include "DSTRING.h"

char *strrev(char *str)
{
	char *p1, *p2;
	
	if (! str || ! *str)
		return str;
	for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
	{
		*p1 ^= *p2;
		*p2 ^= *p1;
		*p1 ^= *p2;
	}
	return str;
}

char* strlwr( char* s )
{
	char* p = s;
	while ((*p = tolower( *p ))) p++;
	return s;
}
