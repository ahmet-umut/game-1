module;
#include <iostream>
export module obstacle;
using namespace std;
export class Obstacle
{
	public:
	void draw()
	{
		// Draw the obstacle
		cout << "Drawing obstacle" << endl;
	}
};