module;
#include <iostream>
#include <X11/Xlib.h>
export module line_obstacle;
#include "../include/Obstacle.hh"
export class LineObstacle: public Obstacle
{
public:
	void draw(Display*display, Window window, GC gc)
	{
		std::cout << "Drawing line obstacle" << std::endl;
	}
};