module;
#include <iostream>
export module soldier;
#include "../include/Entity.hh"
using namespace std;
export class Soldier
{
public:
	char name[2];
	Soldier()
	{
		cout << "Soldier constructed" << endl;
		name[0]='S';
		//direction = rand()%1000/1000.0*2*M_PIf;	//random direction
	}
	void draw()
	{
		cout << "Drawing Soldier" << endl;
		cout << "Name: " << name << endl;
		// Draw the soldier
	}
};