#include "entity.hh"
class Polybolo
{
public:
	Vector position, velocity = {0,0};
	float direction;
	deque<Trajectile> trajects;
	deque<Spear> spears;
	unsigned char defence=0;
	Polybolo()
	{
		position = {rand()%800, rand()%600};
		//direction = rand()%1000/1000.0*2*M_PIf;	//random direction
	}

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

		// Draw the rectangle
		XFillPolygon(display, window, gc, points, 4, Convex, CoordModeOrigin);
	}

	void attack()
	{
		spears.emplace(spears.end(), position.x, position.y, direction);
	}
};