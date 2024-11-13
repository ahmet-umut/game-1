module;
#include <iostream>
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
	void draw()
	{
		cout << "Drawing Soldier" << endl;
		cout << "Name: " << name << endl;
		// Draw the soldier
	}
};