#include "../include/Soldier.hh"
#include <iostream>
using namespace std;

Soldier::Soldier(unordered_multimap<Combatant*,Projectile*>* projectiles, double x, double y) : Combatant(projectiles, x, y)
{
	projectiles->insert({this, new Projectile(x,y,0,255)});	//the inserted projectile is the soldier's spear
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
	projectiles->find(this)->second->position = position;

	task.assess();
	switch (task.state)
	{
	case Task::go:
		velocity = (task.location - position).normalized();
	}
}
bool Soldier::is_around(double x, double y)
{
	Eigen::Vector2d point(x,y);
	return (point - position).norm() < radius;
}