#pragma once
#include "xlib.hh"
#include <eigen3/Eigen/Dense>
#include <deque>
class Entity
{
public:
	Eigen::Vector2d position;	double direction = 0;

	virtual void draw(Display*, Window , GC )=0;
	void execute();
	void attack();
	double distance(Eigen::Vector2d);
	double distance(Entity&);
	Entity(double x, double y) : position(x,y) {}
	Entity(){}
};