#include "../include/Point Obstacle.hh"
#include <iostream>
#include <X11/Xlib.h>
using namespace std;
void PointObstacle::draw(Display*display, Window window, GC gc)
{
	cout << "PointObstacle::draw" << endl;
}
PointObstacle::PointObstacle()
{
	type = point;
	cout << "PointObstacle constructed" << endl;
}