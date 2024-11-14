#pragma once
#include <X11/Xlib.h>
class Obstacle
{
public:
	enum obsttype {point,line} type;
	virtual void draw(Display*display, Window window, GC gc)=0;
};