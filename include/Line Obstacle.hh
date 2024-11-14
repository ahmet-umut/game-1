#pragma once
#include <X11/Xlib.h>
#include "../include/Obstacle.hh"
class LineObstacle: public Obstacle
{
public:
	void draw(Display*display, Window window, GC gc) override;
	LineObstacle();
};