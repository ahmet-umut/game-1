#include "comm.hh"

class Longlive	//abstract class for soldiers and polybolos
{
public:
	Vector position, velocity = {0,0};
	float direction;

	Longlive()
	{
		position = {rand()%800, rand()%600};
		//direction = rand()%1000/1000.0*2*M_PIf;	//random direction
	}

	float distance(Vector&vector)
	{
		return (vector + -position).length();
	}
	float distance(Longlive&entity)
	{
		return (entity.position + -position).length();
	}

	virtual void attack() = 0;
};

class Shortlive	//abstract class for Projectiles and spears
{
public:
	Vector position;	float direction;
	bool tobedeleted = false;

	Shortlive(float x, float y, float direction) : position({x,y}), direction(direction) {}
	Shortlive() : Shortlive(rand()%800, rand()%600, rand()%1000/1000.0*2*M_PIf) {}
	
	#define shlilength (radius<<2)
	virtual void draw()
	{
		XSetForeground(display, gc, encolor);
		Vector start = position;
		Vector end = position + Vector::fromPolar(shlilength, direction);
		XDrawLine(display, window, gc, start.x, start.y, end.x, end.y);
	}
	virtual void execute() = 0;
};
deque<Shortlive*>shortlis;

class Obstacle
{
public:
	enum obsttype {point,line} type;	//0 for point, 1 for line

	//Obstacle(obsttype type) : type(type) {}

	virtual bool isinters(Longlive&entity) = 0;
	virtual Vector correction(Longlive&entity) = 0;
};
deque<Obstacle*>obstacles;