#pragma once
#include "Entity.hh"
#include <eigen3/Eigen/Dense>
class Trajectile : public Entity
{
public:
	double velocity=1, direction;
	unsigned char lifetime = 228;

	Trajectile(double x, double y, double direction=0, unsigned char lifetime=228);
	void draw(Display*display, Window window, GC gc);
	void execute();
};