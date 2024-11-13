module;
#include <iostream>
#include <X11/Xlib.h>
export module soldier;
import vector;
#include "../include/Entity.hh"
using namespace std;
export class Soldier : public Entity
{
public:
	Vector position;
	char name[2];

	Soldier(float x, float y) : position(x,y)
	{
		cout << "Soldier constructed" << endl;
		name[0]='S';
		//direction = rand()%1000/1000.0*2*M_PIf;	//random direction
	}
	void draw(Display*display, Window window, GC gc)
	{
		XSetForeground(display, gc, 0);
		XFillArc(display, window, gc, position.x-9, position.y-9, 2*9, 2*9, 0, 360*64);
	}
};