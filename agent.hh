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
		XDrawPoint(display, window, gc, position.x, position.y);

		if (this==selagent)	XSetForeground(display, gc, secolor);
		else	XSetForeground(display, gc, agcolor);

		#define radius 5
		XDrawArc(display, window, gc, position.x-radius, position.y-radius, 2*radius, 2*radius, 0, 360*64);
	}
	void execute()
	{
		position+=velocity;
		if (task)	task->execute();
	}
};