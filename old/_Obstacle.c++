#include "../include/Obstacle.hh"
#include <iostream>
#include <X11/Xlib.h>
using namespace std;
class Obstacle
{
public:
	enum obsttype {point,line} type;
	virtual void draw(Display*display, Window window, GC gc)=0;
};

export class PointObstacle : public Obstacle
{
public:
	PointObstacle()
	{
		cout << "PointObstacle constructed" << endl;
		type = point;
	}
	void draw(Display*display, Window window, GC gc)
	{
		XSetForeground(display, gc, 0);
		XFillArc(display, window, gc, 100, 100, 9, 9, 0, 360*64);
	}
};
export class LineObstacle : public Obstacle
{
public:
	LineObstacle()
	{
		cout << "LineObstacle constructed" << endl;
		type = line;
	}
	void draw(Display*display, Window window, GC gc)
	{
		XSetForeground(display, gc, 0);
		XDrawLine(display, window, gc, 100, 100, 200, 200);
	}
};