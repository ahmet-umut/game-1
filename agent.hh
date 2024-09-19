#pragma once
#include "task inte.hh"
#include "agent inte.hh"

class Agent : public IAgent
{
public:
	Agent()
	{
		position.x = rand()%800;
		position.y = rand()%600;
		velocity.x = (rand()%100 - 50)/10;
		velocity.y = (rand()%100 - 50)/10;
	}
	using IAgent::IAgent;
	
	void draw()
	{
		if (this==selagent)	XSetForeground(display, gc, secolor);
		else	XSetForeground(display, gc, agcolor);

		XDrawPoint(display, window, gc, position.x, position.y);

		// Draw the weapon held by the right hand
		Vector right_hand = position + Vector::fromPolar(10, direction+M_PI/2) + Vector::fromPolar(weaponpo, direction);
		int weapon_length = 15;
		Vector weapon = right_hand + Vector::fromPolar(weapon_length, direction);
		XDrawLine(display, window, gc, right_hand.x, right_hand.y, weapon.x, weapon.y);

		#define radius 5
		XDrawArc(display, window, gc, position.x-radius, position.y-radius, 2*radius, 2*radius, 0, 360*64);
	}
	void execute()
	{
		position = position+velocity;
		if (task)	task->execute();
		if (weaponpo>0)	weaponpo--;
	}
};