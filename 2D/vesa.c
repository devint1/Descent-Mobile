// Dummy functions that would not be used on modern systems

int  gr_vesa_setmodea(int mode) {
	return 0;
}

int  gr_vesa_checkmode(int mode) {
	return 0;
}

void gr_vesa_setstart(short x, short y) {

}

void gr_vesa_setpage(int page) {

}

void gr_vesa_incpage() {

}

void gr_vesa_scanline(short x1, short x2, short y, unsigned char color) {

}

int  gr_vesa_setlogical(int pixels_per_scanline) {
	return 0;
}

void gr_vesa_bitblt(unsigned char * source_ptr, unsigned int vesa_address, int height, int width) {
	
}

void gr_vesa_pixel(unsigned char color, unsigned int offset) {

}
