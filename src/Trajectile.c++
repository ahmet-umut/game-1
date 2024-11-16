#include "../include/Trajectile.hh"
#include <iostream>
using namespace std;

Trajectile::Trajectile(double x, double y, double direction, unsigned char lifetime) : Entity(x,y), direction(direction), lifetime(lifetime)
{}
void Trajectile::draw(Display*display, Window window, GC gc)
{
	XDrawLine(display, window, gc, position.x(), position.y(), position.x() + 10 * cos(direction), position.y() + 10 * sin(direction));
}
void Trajectile::execute()
{
	position += velocity*Eigen::Vector2d(cos(direction), sin(direction));
	if (lifetime!=255)	lifetime--;	//255 means infinite lifetime
}