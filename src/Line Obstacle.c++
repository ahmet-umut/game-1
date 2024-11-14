#include "../include/Line Obstacle.hh"
#include <iostream>
using namespace std;
void LineObstacle::draw(Display*display, Window window, GC gc)
{
	cout << "LineObstacle::draw" << endl;
	XSetForeground(display, gc, 0);
	XDrawLine(display, window, gc, 100, 100, 200, 200);
}
LineObstacle::LineObstacle()
{
	type = line;
	cout << "LineObstacle constructed" << endl;
}