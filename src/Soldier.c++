#include "../include/Soldier.hh"
#include <iostream>
using namespace std;

Soldier::Soldier(float x, float y) : Entity(x,y)
{
	trajectile = new Trajectile(x,y,0,255);
	cout << "Soldier constructed" << endl;
}
void Soldier::draw(Display*display, Window window, GC gc)
{
	XSetForeground(display, gc, 0);

	XDrawPoint(display, window, gc, position.x(), position.y());

	XDrawArc(display, window, gc, position.x()-radius, position.y()-radius, 2*radius, 2*radius, 0, 360*64);
}
void Soldier::execute()
{
	position += velocity;
	trajectile->position = position;
	//cout << "Soldier::execute" << endl;
}
void Soldier::select()
{
	selsoldier = this;
	cout << "Soldier::select" << endl;
}
bool Soldier::is_around(double x, double y)
{
	Eigen::Vector2d point(x,y);
	return (point - position).norm() < radius;
}