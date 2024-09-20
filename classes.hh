#include "interfaces.hh"

class Task : public ITask
{
public:
	Vector goal;
	IAgent *agent, *target;
	enum {go, attack} type;
	bool active=true;

	Task() : active(false) {}
	Task(IAgent*agent, float x, float y) : agent(agent), goal({x,y}), type(go) {}
	Task(IAgent*agent, IAgent*target) : agent(agent), target(target), type(attack) {}

	void execute()
	{
		if (!active)	return;
		#define maxerror (radius<<2)
		switch (type)
		{
		case go:	//move towards the goal
			if (agent->distance(goal) > maxerror)
			{
				agent->velocity = (goal +- agent->position)/100;
				agent->direction = atan2(goal.y-agent->position.y, goal.x-agent->position.x);
			}
			//else	active = false;
			break;
		case attack:	//attack the target
			if (agent->distance(*target) > maxerror)
			{
				agent->direction = atan2(target->position.y-agent->position.y, target->position.x-agent->position.x);
				agent->velocity = ((*target).position +- agent->position)/100;
			}
			else
			{
				agent->direction = atan2(target->position.y-agent->position.y, target->position.x-agent->position.x)-.4;
				agent->velocity = {0,0};
				agent->attack();
			}
			break;
		
		default:
			break;
		}
		
	}
};

class Agent : public IAgent
{
public:
	inline static Agent*selagent = nullptr;
	float weaponpo=0;
	Task task;

	Agent() {}
	Agent(float velocity) : IAgent(velocity)
	{
		position.x = rand()%800;
		position.y = rand()%600;
	}

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

		XDrawArc(display, window, gc, position.x-radius, position.y-radius, 2*radius, 2*radius, 0, 360*64);
	}
	void attack()
	{
		// Simulate a weapon swing by oscillating the weapon position
		weaponpo += 0.2; // Increment weapon position for a faster swing effect
		if (weaponpo > 1.0 || weaponpo < -1.0) weaponpo = -weaponpo; // Reverse direction after reaching the swing limit
	}
	void assign(Task*task)
	{
		this->task = *task;
	}
	void execute()
	{
		position = position+velocity;
		task.execute();
	}
	virtual float distance(Vector&vector)
	{
		return (vector + -position).length();
	}
	virtual float distance(IAgent&agent)
	{
		return (agent.position + -position).length();
	}
};