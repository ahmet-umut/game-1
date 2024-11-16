#pragma once
#include "xlib.hh"
#include "Entity.hh"
#include <eigen3/Eigen/Dense>
class Polybolo : public Entity
{
public:
	Eigen::Vector2d position;	double direction;

	Polybolo(double x, double y, double direction=0);
	void draw(Display*display, Window window, GC gc);
	void execute();
};