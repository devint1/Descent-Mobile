#include <unistd.h>

#include "GR.H"

// TODO: This is just kind of a hack that "kind of" syncs to the refresh rate of the window
void gr_sync_display() {
    usleep(17000);
}