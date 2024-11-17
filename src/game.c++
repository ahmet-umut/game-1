#include <iostream>
#include <unistd.h>	//for sleep and usleep
#include "../include/xlib.hh"
#include <deque>
using std::deque;
#include <unordered_map>
using std::unordered_multimap;
#include <stdlib.h>  // For drand48() and rand()
#include <eigen3/Eigen/Dense>

#include "../include/Point Obstacle.hh"
#include "../include/Line Obstacle.hh"
#include "../include/Soldier.hh"
#include "../include/Polybolos.hh"
#include "../include/gamestate.hh"
#include "../include/functions.hh"

deque<PointObstacle> point_obstacles;
deque<LineObstacle> line_obstacles;
deque<Soldier> soldiers;
deque<Polybolos> polybolos;

unordered_multimap <Combatant*,Projectile*> projectiles;	//used a map here because we do not want to lose the ownership of some projectiles

#define window_size 255

using Eigen::Vector2d;

void setup_obstacles(unsigned count)
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
void setup_soldiers(unsigned count)
{
	using namespace std;
	cout << "setting up " << (int)count << " soldiers" << endl;
	for (int i = 0; i < count; i++)	soldiers.emplace_back(&projectiles, rand()%window_size, rand()%window_size);
	soldiers[0].position = Vector2d(100,100);
	soldiers[1].position = Vector2d(101,101);
}
void setup_polyboli(unsigned count)
{
	using namespace std;
	cout << "setting up " << (int)count << " polybolos" << endl;
	for (int i = 0; i < count; i++)	polybolos.emplace_back(&projectiles, rand()%window_size, rand()%window_size);
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
	uint clock = 0;
	bool test_flag = false;
	while (1)
	{
		usleep(1000000/60);	//60fps
		switch (state=handle_next_event(state, display, soldiers, polybolos, &test_flag))
		{
		case halt:
			continue;
		case runonce:
			state=halt;
			break;
		case end:
			return;
		}
		using namespace std;
		clock++;
		//std::cout << "game tick: " << (int)clock << std::endl;
		
		if (test_flag)	test();	test_flag = false;
		
		XClearWindow(display, window);

		for (auto& polybolo : polybolos)	polybolo.execute();
		for (auto& soldier : soldiers)
		{
			soldier.execute();
			for (auto& obstacle: point_obstacles)	handle_collision(soldier, &obstacle);
			for (auto& obstacle: line_obstacles)	handle_collision(soldier, &obstacle);
			for (auto& other: soldiers)	handle_collision(soldier, other);
		}
		for (auto iterator = projectiles.begin(); iterator != projectiles.end();)
		{
			iterator->second->execute();
			if (iterator->second->lifetime == 0)
			{
				delete iterator->second;
				iterator = projectiles.erase(iterator);
			}
			else iterator++;
		}
		
		//draw everything
		XSetForeground(display, gc, 0x55dddd);
		XFillRectangle(display, window, gc, 0, 0, window_size, window_size);
		for (auto& polybolo : polybolos)	polybolo.draw(display, window, gc);
		for (auto& soldier : soldiers)	soldier.draw(display, window, gc);
		for (auto& obstacle : point_obstacles)	obstacle.draw(display, window, gc);
		for (auto& obstacle : line_obstacles)	obstacle.draw(display, window, gc);
		for (auto &&[combatant, projectile] : projectiles)	projectile->draw(display, window, gc);
		std::string Projectile_count = "Projectile count on the scene: " + std::to_string(projectiles.size());
		XDrawString(display, window, gc, 10, 10, Projectile_count.c_str(), Projectile_count.size());
	}
}

import x_utilities;
//#include "../include/x utilities.hh"
int main(int argc, char *argv[])
{
	xsetupwindow("game", display, window, gc, 255,255);

	// Initialize the random number generator
	//srand(time(nullptr));

	setup_obstacles(3);
	setup_soldiers(3);
	setup_polyboli(1);

	gameloop();	//returns when the game is over

	xcleanup(display, window, gc);
	return 0;
}