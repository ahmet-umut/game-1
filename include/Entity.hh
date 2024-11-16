#pragma once
#include "xlib.hh"
#include <eigen3/Eigen/Dense>
#include <deque>
class Entity
{
public:
	Eigen::Vector2d position;
	std::deque<Entity*>* trajectiles = (std::deque<Entity*>*)0xff;

	virtual void draw(Display*, Window , GC )=0;
	void execute();
	void attack();
	double distance(Entity&);
	Entity(double x, double y) : position(x,y) {}
	Entity(){}
};