#include "FIX.H"
#include <sys/time.h>

struct timeval start;

void timer_init() {
	gettimeofday(&start, 0);
}

void timer_close() {

}

void timer_set_rate(int count_val) {

}

void timer_set_function(void * function) {

}

fix timer_get_fixed_seconds() {
	struct timeval end;
	double elapsed_s;
	
	gettimeofday(&end, 0);
	elapsed_s = ((double)end.tv_sec + end.tv_usec * 1e-6f) - ((double)start.tv_sec + start.tv_usec * 1e-6f);
	return fl2f(elapsed_s);
}

fix timer_get_fixed_secondsX() {
	return timer_get_fixed_seconds();
}

fix timer_get_approx_seconds() {
	return timer_get_fixed_seconds();
}

long timer_get_usecs() {
	struct timeval end;
	
	gettimeofday(&end, 0);
	return (end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec);
}

void timer_set_joyhandler(void(*joy_handler)()) {

}
