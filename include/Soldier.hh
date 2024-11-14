#pragma once
#include "Entity.hh"
#include <X11/Xlib.h>
#undef Success
#include <eigen3/Eigen/Core>
class Soldier : public Entity
{
public:
	Eigen::Vector2d position;
	char name[2];

	Soldier(float x, float y);
	void draw(Display*display, Window window, GC gc);
	void execute();
};