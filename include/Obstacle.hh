#include <iostream>
#include <X11/Xlib.h>
using namespace std;
class Obstacle
{
public:
	enum obsttype {point,line} type;
	virtual void draw(Display*display, Window window, GC gc)=0;
};