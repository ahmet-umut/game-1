#pragma once
#include "xlib.hh"
#include "Entity.hh"
#include <eigen3/Eigen/Dense>
class Polybolo : public Entity
{
public:
	Eigen::Vector2d position;
	Polybolo(double x, double y);
	void draw(Display*display, Window window, GC gc);
	void execute();
};