#include <string.h>

void gr_linear_stosd(void * source, unsigned char color, unsigned short nbytes) {
	memset(source, color, nbytes);
}
