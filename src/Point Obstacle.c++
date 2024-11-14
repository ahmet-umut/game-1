module;
#include <iostream>
#include <X11/Xlib.h>
export module point_obstacle;
#include "../include/Obstacle.hh"
export class PointObstacle: public Obstacle
{
public:
	void draw(Display*display, Window window, GC gc)
	{
		std::cout << "Drawing point obstacle" << std::endl;
	}
};