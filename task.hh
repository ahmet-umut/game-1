#pragma once
#include "task.hh"
#include "agent.hh"

class Task : virtual public ITask
{
public:
    using ITask::ITask;
	void execute()
	{
		//move towards the goal
		#define maxerror 1
		if (active)	if ((goal.x-agent->position.x)*(goal.x-agent->position.x) + (goal.y-agent->position.y)*(goal.y-agent->position.y) > maxerror*maxerror)
		{
			agent->velocity.x = (goal.x-agent->position.x)/100;
			agent->velocity.y = (goal.y-agent->position.y)/100;
			agent->direction = atan2(goal.y-agent->position.y, goal.x-agent->position.x);
		}
		//else	active = false;
	}
};