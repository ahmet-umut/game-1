module;
#include <iostream>
#include <X11/Xlib.h>
export module polybolo;
#include "../include/Entity.hh"
using namespace std;
export class Polybolo : public Entity
{
public:
	char name[2];
	Polybolo()
	{
		cout << "Polybolo constructed" << endl;
		name[0]='O';
		//direction = rand()%1000/1000.0*2*M_PIf;	//random direction
	}
	void draw(Display*display, Window window, GC gc)
	{
		cout << "Drawing Polybolo" << endl;
		cout << "Name: " << name << endl;
		// Draw the polybolo
	}
	void execute()
	{
		cout << "Executing Polybolo" << endl;
		// Execute the polybolo
	}
};