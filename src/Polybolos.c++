#include "../include/Polybolos.hh"
#include <iostream>
using namespace std;

bool Polybolos::is_around(double x, double y)
{
	Eigen::Vector2d point(x,y);
	return (point - position).norm() < 5;	//5 is the estimated radius of the polybolo
}
void Polybolos::draw(Display*display, Window window, GC gc)
{
	if (this == Combatant::selected_combatant)	XSetForeground(display, gc, 0xdd555d);
	else	XSetForeground(display, gc, 0x55555d);

	XRectangle rectangles[2];
	rectangles[0].x = position.x() - 5;
	rectangles[0].y = position.y() - 5;
	rectangles[0].width = 11;
	rectangles[0].height = 11;

	#define rect_width 3
	rectangles[1].x = position.x() - rect_width/2 + 11 * cos(direction);
	rectangles[1].y = position.y() - rect_width/2 + 11 * sin(direction);
	rectangles[1].width = rect_width;
	rectangles[1].height = rect_width;
	XDrawRectangles(display, window,gc, rectangles, 2);
}
void Polybolos::execute()
{
	if (task.state == Task::attack)
	{
		direction = atan2(task.target->position.y() - position.y(), task.target->position.x() - position.x());
		if (cooldown==0)	fire(), cooldown=cooldowntime;
		cooldown--;
	}
}
Projectile Polybolos::fire()
{
	Projectile* projectile = new Projectile(position.x(), position.y(), direction);
	projectiles->insert({this, projectile});

	cout << "Polybolos::fire" << endl;
	
	return *projectile;
}
