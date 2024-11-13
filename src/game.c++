#include <iostream>
#include <unistd.h>	//for sleep and usleep
#include <X11/Xlib.h>
#include <deque>

import obstacle;
deque<Obstacle> obstacles;

void setup_obstacles(unsigned char count)
{
	using namespace std;
	cout << "setting up " << (int)count << " obstacles" << endl;
	for (int i = 0; i < count; i++)
	{
		switch (rand()%2)
		{
		case 0:
			cout << "adding point obstacle" << endl;
			break;
		case 1:
			cout << "adding line obstacle" << endl;
			break;
		}
	}
}

Display *display;	Window window;	GC gc;

import handle_next_event;
#include "../include/gamestate.hh"
void gameloop()
{
	gamestate state = running;
	while (1)
	{
		handle_next_event(state, display);
		switch (state)
		{
		case halt:
			continue;
		case runonce:
			state=halt;
			break;
		case end:
			return;
		}
		std::cout << "game tick" << std::endl;
		sleep(1);
	}
}

import x_utilities;
//#include "../include/x utilities.hh"
int main(int argc, char *argv[])
{
	xsetupwindow("ray tracer", display, window, gc,255,255);

	// Initialize the random number generator
	//srand(time(nullptr));

	setup_obstacles(2);

	gameloop();	//returns when the game is over

	xcleanup(display, window, gc);
	return 0;
}