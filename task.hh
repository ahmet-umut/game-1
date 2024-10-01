#include "comm.hh"
#include "entity.hh"

class Task
{
public:
	Vector goal, starting;	deque<Vector>path;
	Entity *soldier, *target;
	enum {go, attack} type;
	bool active=true;

	#define maxerror (radius<<2)

	Task() : active(false) {}
	Task(Entity*soldier, float x, float y) : soldier(soldier), goal({x,y}), type(go)
	{
		Vector current = starting = soldier->position;
		while ((current + -goal).length() > maxerror)
		{
			Vector delta = (goal + -current) * maxerror / (goal+-current).length();
			for (auto &&obst : obstacles)	if (obst->type == obst->line)	if (LineSegment(current,delta).isIntersecting(obst->lineSegment))
			{
				path.emplace(path.end(), delta);
				break;
			}
			if (LineSegment(current,delta).isIntersecting)
			path.emplace(path.end(), delta);
			end = end + delta;
		}
	}
	Task(Entity*soldier, Entity*target) : soldier(soldier), target(target), type(attack) {}

	void execute()
	{
		if (!active)	return;
		switch (type)
		{
		case go:	//move towards the goal
			if (soldier->distance(goal) > maxerror)
			{
				soldier->velocity = (goal +- soldier->position)/100;
				soldier->direction = atan2(goal.y-soldier->position.y, goal.x-soldier->position.x);
			}
			//else	active = false;
			break;
		case attack:	//attack the target
			if (soldier->distance(*target) > maxerror)
			{
				soldier->direction = atan2(target->position.y-soldier->position.y, target->position.x-soldier->position.x);
				soldier->velocity = ((*target).position +- soldier->position)/100;
			}
			else
			{
				soldier->direction = atan2(target->position.y-soldier->position.y, target->position.x-soldier->position.x)-.4;
				soldier->velocity = {0,0};
				soldier->attack();
			}
			break;
		
		default:
			break;
		}
		
	}
};
