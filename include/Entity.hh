#pragma once
#include <X11/Xlib.h>
class Entity
{
public:
	float x, y;
	void draw(Display*, Window , GC );
	void execute();
	void attack();
};