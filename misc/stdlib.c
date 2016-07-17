//
// Created by devin on 7/17/16.
//
// Some Android versions have these as regular functions and some have them defined as static
// inline, so just define our own to avoid link errors
//
#include <stddef.h>

extern long lrand48(void);
extern void srand48(long);
extern double strtod(const char *nptr, char **endptr);

int rand() {
	return (int) lrand48();
}

void srand(unsigned int __s) {
	srand48(__s);
}

double atof(const char *nptr) {
	return (strtod(nptr, NULL));
}
