#include <iostream>
#include <unistd.h>	//for sleep and usleep
#include <X11/Xlib.h>
#include <deque>
using std::deque;

import obstacle;
deque<Obstacle> obstacles;
import soldier;
deque<Soldier> soldiers;
import polybolo;
deque<Polybolo> polybolos;

void setup_obstacles(unsigned char count)
{
	using namespace std;
	cout << "setting up " << (int)count << " obstacles" << endl;
	for (int i = 0; i < count; i++)
	{
		obstacles.emplace_back();
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
void setup_soldiers(unsigned char count)
{
	using namespace std;
	cout << "setting up " << (int)count << " soldiers" << endl;
	for (int i = 0; i < count; i++)	soldiers.emplace_back();
}
void setup_polybolos(unsigned char count)
{
	using namespace std;
	cout << "setting up " << (int)count << " polybolos" << endl;
	for (int i = 0; i < count; i++)	polybolos.emplace_back();
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
		XClearWindow(display, window);

		for (auto& polybolo : polybolos)	polybolo.draw();
		for (auto& soldier : soldiers)	soldier.draw();

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
	setup_soldiers(1);
	setup_polybolos(1);

	gameloop();	//returns when the game is over

	xcleanup(display, window, gc);
	return 0;
}