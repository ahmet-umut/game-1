#include "../include/Soldier.hh"
#include "../include/functions.hh"
#include <iostream>
using namespace std;
using namespace Eigen;

Vector2d polar(double length, double angle)
{
	return Vector2d(cos(angle), sin(angle))*length;
}

Soldier::Soldier(unordered_multimap<Combatant*,Projectile*>* projectiles, double x, double y) : Combatant(projectiles, x, y)
{
	projectiles->insert({this, new Projectile(x,y,0,255)});	//the inserted projectile is the soldier's spear
}
void Soldier::draw(Display*display, Window window, GC gc)
{
	if (this == Combatant::selected_combatant)	XSetForeground(display, gc, 0xdd555d);
	else	XSetForeground(display, gc, 0x55555d);
	
	XDrawPoint(display, window, gc, position.x(), position.y());
	XDrawArc(display, window, gc, position.x()-radius, position.y()-radius, 2*radius, 2*radius, 0, 360*64);
}
void Soldier::execute()
{
	Projectile* sword = projectiles->find(this)->second;
	position += velocity;
	if (velocity.norm() > 0)	direction = atan2(velocity.y(), velocity.x()), sword->direction = direction-.1;	//if the soldier is standing still, the direction cannot be determined from the velocity, so do not edit the direction.
	sword->position = position + polar(radius, direction + M_PI_2);

	auto old_state = task.state;
	task.assess();
	switch (task.state)
	{
	case Task::go:
		velocity = (task.location - position).normalized();
		break;
	default:
		if (old_state == Task::go) velocity = {0,0};
	}
}
bool Soldier::is_around(double x, double y)
{
	Eigen::Vector2d point(x,y);
	return (point - position).norm() < radius;
}