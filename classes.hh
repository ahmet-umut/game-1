#include "interfaces.hh"

class Spear : public Shortlive
{
public:
	using Shortlive::Shortlive;
	void execute()	{}
};

class Task
{
public:
	Vector goal, starting;	deque<Vector>path;
	Longlive *soldier, *target;
	enum {go, attack} type;
	bool active=true;

	#define maxerror (radius<<2)

	Task() : active(false) {}
	Task(Longlive*soldier, float x, float y) : soldier(soldier), goal({x,y}), type(go)
	{
		Vector current = starting = soldier->position;
		while ((current + -goal).length() > maxerror)
		{
			Vector delta = (goal + -current) * maxerror / (goal+-current).length();
			if
			path.emplace(path.end(), delta);
			end = end + delta;
		}
	}
	Task(Longlive*soldier, Longlive*target) : soldier(soldier), target(target), type(attack) {}

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

class Trajecti: public Shortlive
{
public:
	char velocity=0;

	Trajecti(float x, float y, float direction, char velocity) : Shortlive(x, y, direction), velocity(velocity) {}

	void execute()
	{
		if (velocity == 0)
		{
			tobedeleted = true;
			return;
		}
		if (abs(velocity) < 16)	velocity -= abs(velocity)/velocity;
		else 
		{
			#define k (1<<4)
			bool positive = velocity>0;
			velocity -= (abs(velocity)/k) * (velocity/k);
			if (positive != velocity>0)	velocity = 0;
		}
		position = position + Vector::fromPolar(velocity, direction);
	}
};

class Polybolo : public Longlive
{
public:
	/* ~Polybolo()	//need to delete them manually since they are not dynamically allocated
	{
		for (auto iterator = shortlis.begin(); iterator != shortlis.end(); ++iterator)
			for (auto&&trajecti: trajects)
				if (&trajecti==*iterator)	iterator = shortlis.erase(iterator);
	} */
	void draw()
	{
		XSetForeground(display, gc, encolor);
		xpoint points[4];

		// Calculate the four corners of the rectangle
		Vector corners[4] = {
			{-10, -10},
			{10, -10},
			{10, 10},
			{-10, 10}
		};

		// Rotate the corners based on the direction
		for (int i = 0; i < 4; ++i) {
			float x_new = corners[i].x * cos(direction) - corners[i].y * sin(direction);
			float y_new = corners[i].x * sin(direction) + corners[i].y * cos(direction);
			points[i].x = position.x + x_new;
			points[i].y = position.y + y_new;
		}

		XDrawLines(display, window, gc, points, 4, CoordModeOrigin);
	}
	void attack()
	{
		shortlis.push_back(new Trajecti(position.x, position.y, direction, 16));
	}
};

class Soldier : public Longlive
{
public:
	inline static Soldier*selsoldier = nullptr;
	Task task;
	unsigned char defence=0;	//used in Soldier::gethit() function.

	Spear*spear;
	float weaponpo=0;

	struct {bool team, autoatta;} properts;

	~Soldier()
	{
		spear->tobedeleted = true;
	}

	Soldier() : Longlive()
	{
		//Vector trajectile_start = position + Vector::fromPolar(10, direction+M_PI/2);
		cout << shortlis.size() << endl;
		spear = new Spear(position.x, position.y, direction);
		shortlis.push_back(spear);
		cout << shortlis.size() << endl;
	}

	void draw()
	{
		if (this==selsoldier)	XSetForeground(display, gc, secolor);
		else	XSetForeground(display, gc, encolor);

		XDrawPoint(display, window, gc, position.x, position.y);
		
		Vector start = task.starting;
		for (auto&&delta: task.path)
		{
			Vector end = start + delta;
			XDrawLine(display, window, gc, start.x, start.y, end.x, end.y);
			start = end;
		}

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
		spear->position = position + Vector::fromPolar(10, direction+M_PI/2) + Vector::fromPolar(weaponpo, direction);
		spear->direction = direction;		
		position = position+velocity;
		task.execute();
	}
	float isaround(Vector point)
	{
		return (point +- position).length() < radius;
	}
	void gethit()	//Returns 1/(defence+1) probability 
	{
		cout << "shoot ";
		if (rand()%(defence+1)==0)	cout << "dead";
		cout << endl;
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
