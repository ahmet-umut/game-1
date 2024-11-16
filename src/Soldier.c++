#include "../include/Soldier.hh"
#include <iostream>
using namespace std;

Soldier::Soldier(float x, float y) : position(x,y)
{
	cout << "Soldier constructed" << endl;
	//direction = rand()%1000/1000.0*2*M_PIf;	//random direction
}
void Soldier::draw(Display*display, Window window, GC gc)
{
	XSetForeground(display, gc, 0);

	XDrawPoint(display, window, gc, position.x(), position.y());

	XDrawArc(display, window, gc, position.x()-radius, position.y()-radius, 2*radius, 2*radius, 0, 360*64);
}
void Soldier::execute()
{
	cout << "Soldier::execute" << endl;
}