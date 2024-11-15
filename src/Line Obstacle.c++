#include "../include/Line Obstacle.hh"
#include <eigen3/Eigen/Dense>
#include <iostream>
using namespace Eigen;
using namespace std;
void LineObstacle::draw(Display*display, Window window, GC gc)
{
	cout << "LineObstacle::draw" << endl;
	XSetForeground(display, gc, 0);
	XDrawLine(display, window, gc, lineSegment.start.x(), lineSegment.start.y(), (lineSegment.start + lineSegment.delta).x(), (lineSegment.start + lineSegment.delta).y());
}
LineObstacle::LineObstacle()
{
	type = line;
	cout << "LineObstacle constructed" << endl;
}
LineObstacle::LineObstacle(double x1, double y1, double x2, double y2) : lineSegment(Vector2d(x1,y1), Vector2d(x2,y2))
{
	type = line;
	cout << "LineObstacle constructed" << endl;
}