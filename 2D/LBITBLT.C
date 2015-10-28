#include "GR.H"

void gr_merge_textures(ubyte * lower, ubyte * upper, ubyte * dest) {
	int x, y, h;
	unsigned char c;
	for (y = 0; y < 64; y++)
		for (x = 0; x < 64; x++) {
			h = (64 * y + x);
			c = upper[h];
			if (c == 255)
				c = lower[h];
			*dest++ = c;
		}
}

void gr_merge_textures_1(ubyte * lower, ubyte * upper, ubyte * dest) {
	int x, y, h;
	unsigned char c;
	for (y = 0; y < 64; y++)
		for (x = 0; x < 64; x++) {
			c = upper[64 * x + (63 - y)];
			if (c == 255)
				c = lower[64 * y + x];
			*dest++ = c;
		}
}

void gr_merge_textures_2(ubyte * lower, ubyte * upper, ubyte * dest) {
	int x, y, h;
	unsigned char c;
	for (y = 0; y < 64; y++)
		for (x = 0; x < 64; x++) {
			c = upper[64 * (63 - y) + (63 - x)];
			if (c == 255)
				c = lower[64 * y + x];
			*dest++ = c;
		}

}

void gr_merge_textures_3(ubyte * lower, ubyte * upper, ubyte * dest) {
	int x, y, h;
	unsigned char c;
	for (y = 0; y < 64; y++)
		for (x = 0; x < 64; x++) {
			c = upper[64 * (63 - x) + y];
			if (c == 255)
				c = lower[64 * y + x];
			*dest++ = c;

		}
}
