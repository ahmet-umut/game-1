#include "interfaces.hh"

class Task : public ITask
{
public:
	Vector goal;
	ISoldier *soldier, *target;
	enum {go, attack} type;
	bool active=true;

	Task() : active(false) {}
	Task(ISoldier*soldier, float x, float y) : soldier(soldier), goal({x,y}), type(go) {}
	Task(ISoldier*soldier, ISoldier*target) : soldier(soldier), target(target), type(attack) {}

	void execute()
	{
		if (!active)	return;
		#define maxerror (radius<<2)
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

class Soldier : public ISoldier
{
public:
	inline static Soldier*selsoldier = nullptr;
	float weaponpo=0;
	Task task;
	unsigned char defence=0;	//used in Soldier::gethit() function.
	unsigned char army=0;

	Soldier() {}
	Soldier(float velocity) : ISoldier(velocity)
	{
		position.x = rand()%800;
		position.y = rand()%600;
	}

	void draw()
	{
		if (this==selsoldier)	XSetForeground(display, gc, secolor);
		else	XSetForeground(display, gc, agcolor);

		XDrawPoint(display, window, gc, position.x, position.y);

		// Draw the weapon held by the right hand
		Vector weaponst = position + Vector::fromPolar(10, direction+M_PI/2) + Vector::fromPolar(weaponpo, direction);
		#define weaponle 15
		Vector weaponen = weaponst + Vector::fromPolar(weaponle, direction);
		XDrawLine(display, window, gc, weaponst.x, weaponst.y, weaponen.x, weaponen.y);

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
	virtual float distance(ISoldier&soldier)
	{
		return (soldier.position + -position).length();
	}
	float isaround(Vector point)
	{
		return (point +- position).length() < radius;
	}
	void gethit()	//Returns 1/(defence+1) probability 
	{
		//cout << (rand()%(defence+1)==0) << endl;
	}
};

class Pointobs
{
public:
	Vector position;
	Pointobs(Vector position) : position(position) {}
	bool isinters(Soldier&soldier)
	{
		if (soldier.isaround(position))	return true;	return false;
	}
	Vector correction(Soldier&soldier)
	{
		return (soldier.position + -position) * (radius - soldier.distance(position));
	}
};
class Lineobs
{
public:
	Vector point1,point2;
	Lineobs(Vector point1, Vector point2) : point1(point1), point2(point2) {}
	bool isinters(Soldier&soldier)
	{
		Vector intersec;
		Vector middle = (point1 + point2) / 2, difference = point2 + -point1;
		short int v1 = difference.x;
		short int v2 = difference.y;
		short int v3 = middle.y - middle.x*v2/v1;
		short int v4 = soldier.position.y + soldier.position.x*v1/v2;
		intersec.x = (v4-v3)*v1*v2 / (float)(v1*v1 + v2*v2);
		intersec.y = intersec.x*v2/v1 + v3;

		if (soldier.isaround(point1) || soldier.isaround(point2))	return true;
		if (soldier.isaround(intersec) && (intersec.x < point1.x && intersec.x > point2.x || intersec.x > point1.x && intersec.x < point2.x))	return true;	//if the intersection is inside the line segment and the soldier is around the intersection
		return false;
	}
	Vector correction(Soldier&soldier)
	{
		Vector intersec;
		Vector middle = (point1 + point2) / 2, difference = point2 + -point1;
		short int v1 = difference.x;
		short int v2 = difference.y;
		short int v3 = middle.y - middle.x*v2/v1;
		short int v4 = soldier.position.y + soldier.position.x*v1/v2;
		intersec.x = (v4-v3)*v1*v2 / (float)(v1*v1 + v2*v2);
		intersec.y = intersec.x*v2/v1 + v3;

		if (!(intersec.x < point1.x && intersec.x > point2.x || intersec.x > point1.x && intersec.x < point2.x))
			if (soldier.isaround(point1))	return (soldier.position + -point1) * (radius - soldier.distance(point1));
			else						return (soldier.position + -point2) * (radius - soldier.distance(point2));

		return (soldier.position + -intersec) * (radius - soldier.distance(intersec));		
	}
};

/*
p1,p2,a

x1 y1 x2 y2 x0 y0
y = a1*x + b1	a1 b1
y = a2*x + b2	a2 b2
x. y.
distance(x.,y., x0,y0)

a1 = (y2-y1) / (x2-x1)
b1 = y1 - x1*a1
a2 = -1/a1
b2 = y0 - x0/a2
x. = (b1-b2) / -(a1-a2)
y. = x.*a1 + b1
*/