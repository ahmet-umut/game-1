#pragma once
#include "xlib.hh"
class Obstacle
{
public:
	enum obsttype {point,line} type;
	virtual void draw(Display*display, Window window, GC gc)=0;
};