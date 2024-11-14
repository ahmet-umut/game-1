#include "../include/Soldier.hh"
#include <iostream>
#include <X11/Xlib.h>
using namespace std;
Soldier::Soldier(float x, float y) : position(x,y)
{
	cout << "Soldier constructed" << endl;
	name[0]='S';
	//direction = rand()%1000/1000.0*2*M_PIf;	//random direction
}
void Soldier::draw(Display*display, Window window, GC gc)
{
	cout << "Soldier::draw" << endl;
	XSetForeground(display, gc, 0);
	XFillArc(display, window, gc, position.x()-9, position.y()-9, 2*9, 2*9, 0, 360*64);
}
void Soldier::execute()
{
	cout << "Soldier::execute" << endl;
}