#include "../include/Polybolo.hh"
#include <iostream>
#include <X11/Xlib.h>
using namespace std;

Polybolo::Polybolo()
{
	cout << "Polybolo constructed" << endl;
	name[0]='O';
	//direction = rand()%1000/1000.0*2*M_PIf;	//random direction
}
void Polybolo::draw(Display*display, Window window, GC gc)
{
	cout << "Drawing Polybolo" << endl;
	cout << "Name: " << name << endl;
	// Draw the polybolo
}
void Polybolo::execute()
{
	cout << "Executing Polybolo" << endl;
	// Execute the polybolo
}