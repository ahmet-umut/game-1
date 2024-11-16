#pragma once
#include "Entity.hh"
#include "xlib.hh"
#include <eigen3/Eigen/Core>
class Soldier : public Entity
{
public:
	Eigen::Vector2d position, velocity = {0,0};
	static constexpr double radius = 11;

	Soldier();
	Soldier(float x, float y);
	void draw(Display*display, Window window, GC gc);
	void execute();
};