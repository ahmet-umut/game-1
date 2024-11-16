#include "../include/Polybolo.hh"
#include <iostream>
using namespace std;

Polybolo::Polybolo(deque<Trajectile*>*trajectiles, double x, double y, double direction) : Entity(x,y), direction(direction), trajectiles(trajectiles)
{}
void Polybolo::draw(Display*display, Window window, GC gc)
{
	XRectangle rectangles[2];
	rectangles[0].x = position.x() - 5;
	rectangles[0].y = position.y() - 5;
	rectangles[0].width = 11;
	rectangles[0].height = 11;

	rectangles[1].x = position.x() + 11 * cos(direction);
	rectangles[1].y = position.y() + 11 * sin(direction);
	rectangles[1].width = 2;
	rectangles[1].height = 2;
	XDrawRectangles(display, window,gc, rectangles, 2);
}
void Polybolo::execute()
{
	//cout << "Executing Polybolo" << endl;
	// Execute the polybolo
}
Trajectile Polybolo::fire()
{
	Trajectile* trajectile = new Trajectile(position.x(), position.y(), direction);
	trajectiles->push_back(trajectile);
	return *trajectile;
}