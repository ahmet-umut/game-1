#include <iostream>
#include <unistd.h>	//for sleep and usleep
#include "../include/xlib.hh"
#include <deque>
using std::deque;
#include <stdlib.h>  // For drand48() and rand()
#include <eigen3/Eigen/Dense>

#include "../include/Point Obstacle.hh"
#include "../include/Line Obstacle.hh"
#include "../include/Soldier.hh"
#include "../include/Polybolo.hh"
#include "../include/gamestate.hh"
#include "../include/functions.hh"

deque<PointObstacle> point_obstacles;
deque<LineObstacle> line_obstacles;
deque<Soldier> soldiers;
deque<Polybolo> polybolos;

using Eigen::Vector2d;

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
			point_obstacles.emplace_back(rand()%255, rand()%255);
			break;
		case 1:
			cout << "adding line obstacle" << endl;
			line_obstacles.emplace_back(rand()%255, rand()%255,rand()%255, rand()%255);
			break;
		}
	}
}
void setup_soldiers(unsigned char count)
{
	using namespace std;
	cout << "setting up " << (int)count << " soldiers" << endl;
	for (int i = 0; i < count; i++)	soldiers.emplace_back(rand()%255, rand()%255);
}
void setup_polybolos(unsigned char count)
{
	using namespace std;
	cout << "setting up " << (int)count << " polybolos" << endl;
	for (int i = 0; i < count; i++)	polybolos.emplace_back(rand()%255, rand()%255);
}

Display *display;	Window window;	GC gc;

import handle_next_event;
void gameloop()
{
	gamestate state = running;
	unsigned char clock = 0;
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
		clock++, std::cout << "game tick: " << (int)clock << std::endl;
		XClearWindow(display, window);

		for (auto& polybolo : polybolos)
		{
			polybolo.draw(display, window, gc);
			polybolo.execute();
		}
		for (auto& soldier : soldiers)
		{
			soldier.draw(display, window, gc);
			soldier.execute();
			/* for (auto& other: soldiers)	handle_collision(soldier, other);
			for (auto& obstacle: point_obstacles)	handle_collision(soldier, &obstacle);
			for (auto& obstacle: line_obstacles)	handle_collision(soldier, &obstacle); */
		}	
		for (auto& obstacle : point_obstacles)	obstacle.draw(display, window, gc);
		for (auto& obstacle : line_obstacles)	obstacle.draw(display, window, gc);

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

	setup_obstacles(3);
	setup_soldiers(2);
	setup_polybolos(1);

	gameloop();	//returns when the game is over

	xcleanup(display, window, gc);
	return 0;
}