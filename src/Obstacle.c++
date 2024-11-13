module;
#include <iostream>
#include <X11/Xlib.h>
export module obstacle;
using namespace std;
export class Obstacle
{
public:
	void draw(Display*display, Window window, GC gc)
	{
		// Draw the obstacle
		cout << "Drawing obstacle" << endl;
	}
};