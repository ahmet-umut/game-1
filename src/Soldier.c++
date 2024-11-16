#include "../include/Soldier.hh"
#include <iostream>
using namespace std;

Soldier::Soldier(deque<Entity*>*trajectiles, double x, double y) : Entity(x,y)
{
	this->trajectiles = trajectiles;
	trajectiles->push_back(new Trajectile(x,y,0,255));
	trajectile_indice = trajectiles->size()-1;
	((Trajectile*)(trajectiles->at(trajectile_indice)))->velocity = 0;
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
	//trajectiles->at(trajectile_indice)->position = position;
	//trajectile->position = position;
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