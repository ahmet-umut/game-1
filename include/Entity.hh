#pragma once
#include "xlib.hh"
class Entity
{
public:
	float x, y;
	void draw(Display*, Window , GC );
	void execute();
	void attack();
};