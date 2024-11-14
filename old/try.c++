#include "x utilities.hh"
#include <unistd.h>
Display *display;	Window window;	GC gc;
int main()
{
	xsetupwindow("game", display, window, gc);
	pause();

	xcleanup(display, window, gc);
	return 0;
}