#include "../include/Projectile.hh"
#include <iostream>
using namespace std;

Projectile::Projectile(double x, double y, double direction, unsigned char lifetime) : Entity(x,y), direction(direction), lifetime(lifetime)
{}
void Projectile::draw(Display*display, Window window, GC gc)
{
	XSetForeground(display, gc, 0x55555d);
	XDrawLine(display, window, gc, position.x(), position.y(), position.x() + 22 * cos(direction), position.y() + 22 * sin(direction));
}
void Projectile::execute()
{
	position += velocity*Eigen::Vector2d(cos(direction), sin(direction));
	if (lifetime!=255)	lifetime--;	//255 means infinite lifetime
}