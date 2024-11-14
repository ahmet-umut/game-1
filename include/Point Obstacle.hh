#pragma once
#include <X11/Xlib.h>
#include "Obstacle.hh"
class PointObstacle : public Obstacle
{
public:
	void draw(Display*display, Window window, GC gc);
	PointObstacle();
};