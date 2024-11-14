#pragma once
#include <X11/Xlib.h>
#include "Entity.hh"
class Polybolo : public Entity
{
public:
	char name[2];
	Polybolo();
	void draw(Display*display, Window window, GC gc);
	void execute();
};