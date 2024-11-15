#include "../include/Point Obstacle.hh"
#include <iostream>
using namespace std;
void PointObstacle::draw(Display*display, Window window, GC gc)
{
	#define indicato 9
	for (unsigned char cursor = 0; cursor < indicato; cursor++)
	{
		XDrawPoint(display, window, gc, position.x()+cursor, position.y());
		XDrawPoint(display, window, gc, position.x()-cursor, position.y());
		XDrawPoint(display, window, gc, position.x(), position.y()+cursor);
		XDrawPoint(display, window, gc, position.x(), position.y()-cursor);
	}
}
PointObstacle::PointObstacle(double x, double y) : position(x,y)
{
	type = point;
	cout << "PointObstacle constructed" << endl;
}