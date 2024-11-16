#pragma once
#include "Entity.hh"
#include "Trajectile.hh"
#include "xlib.hh"
#include <eigen3/Eigen/Dense>
#include <deque>
class Polybolo : public Entity
{
public:
	Eigen::Vector2d velocity;	double direction;

	Polybolo(std::deque<Entity*>*, double , double , double=0);

	void draw(Display*display, Window window, GC gc);
	void execute();
	Trajectile fire();
};