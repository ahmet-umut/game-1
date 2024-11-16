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
deque<Trajectile*> trajectiles;

#define window_size 255

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
			point_obstacles.emplace_back(rand()%window_size, rand()%window_size);
			break;
		case 1:
			cout << "adding line obstacle" << endl;
			line_obstacles.emplace_back(rand()%window_size, rand()%window_size,rand()%window_size, rand()%window_size);
			break;
		}
	}
}
void setup_soldiers(unsigned char count)
{
	using namespace std;
	cout << "setting up " << (int)count << " soldiers" << endl;
	for (int i = 0; i < count; i++)	soldiers.emplace_back(rand()%window_size, rand()%window_size);
}
void setup_polyboli(unsigned char count)
{
	using namespace std;
	cout << "setting up " << (int)count << " polybolos" << endl;
	for (int i = 0; i < count; i++)	polybolos.emplace_back(&trajectiles, rand()%window_size, rand()%window_size);
}

Display *display;	Window window;	GC gc;

void test()
{
	std::cout << "testing" << std::endl;
	polybolos[0].fire();
}

void gameloop()
{
	gamestate state = running;
	unsigned char clock = 0;
	bool test_flag = false;
	while (1)
	{
		usleep(1000000/60);	//60fps
		switch (state=handle_next_event(state, display, soldiers, &test_flag))
		{
		case halt:
			continue;
		case runonce:
			state=halt;
			break;
		case end:
			return;
		}
		clock++;
		//std::cout << "game tick: " << (int)clock << std::endl;
		
		if (test_flag)	test();	test_flag = false;
		
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
			for (auto& obstacle: point_obstacles)	handle_collision(soldier, &obstacle);
			for (auto& obstacle: line_obstacles)	handle_collision(soldier, &obstacle);
			for (auto& other: soldiers)	handle_collision(soldier, other);
		}	
		for (auto& obstacle : point_obstacles)	obstacle.draw(display, window, gc);
		for (auto& obstacle : line_obstacles)	obstacle.draw(display, window, gc);
		for (auto iterator = trajectiles.begin(); iterator != trajectiles.end();)
		{
			(*iterator)->draw(display, window, gc);
			(*iterator)->execute();
			if ((*iterator)->lifetime == 0)
			{
				delete *iterator;
				iterator = trajectiles.erase(iterator);
			}
			else iterator++;
		}
		std::string trajectile_count = "trajectile count on the scene: " + std::to_string(trajectiles.size());
		XDrawString(display, window, gc, 10, 10, trajectile_count.c_str(), trajectile_count.size());
	}
}

import x_utilities;
//#include "../include/x utilities.hh"
int main(int argc, char *argv[])
{
	xsetupwindow("ray tracer", display, window, gc, 255,255);

	// Initialize the random number generator
	//srand(time(nullptr));

	setup_obstacles(3);
	setup_soldiers(2);
	setup_polyboli(1);

	gameloop();	//returns when the game is over

	xcleanup(display, window, gc);
	return 0;
}