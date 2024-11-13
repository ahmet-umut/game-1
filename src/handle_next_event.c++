module;
#include "../include/gamestate.hh"
#include <X11/Xlib.h>
export module handle_next_event;
#include <stdio.h>
export gamestate handle_next_event(gamestate state, Display* display)
{
	using namespace std;
	printf("handling next event\n");
	XPending(display);
	return state;
}