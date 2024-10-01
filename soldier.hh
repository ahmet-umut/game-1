#include "spear.hh"
class Soldier: public Entity
{
public:
	static inline Soldier*selsoldier = nullptr;
	static inline const unsigned char radius = 10;

    struct
    {
        unsigned char team : 1;
        unsigned char defence : 1;
    } properties;

    Vector position, velocity = {0,0};
    float direction;
	Spear*spear;

	Soldier() : position({rand()%800, rand()%600}) {}
    Soldier(bool team) : Soldier()
	{
		properties.team = team;
	}

    float distance(Vector&vector)
    {
        return (vector + -position).length();
    }
    float distance(Soldier&soldier)
    {
        return (soldier.position + -position).length();
    }

	bool isaround(Vector point)
	{
		return (point + -position).length() < radius;
	}
	bool isaround(float x, float y)
	{
		return isaround({x,y});
	}

	void draw()
	{
		XSetForeground(display, gc, properties.team ? secolor : encolor);
		XFillArc(display, window, gc, position.x-radius, position.y-radius, 2*radius, 2*radius, 0, 360*64);
	}
	void execute()
	{
		position = position + velocity;
	}
};