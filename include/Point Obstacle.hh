#pragma once
#include "xlib.hh"
#include "Obstacle.hh"
#undef Success
#include <eigen3/Eigen/Dense>
class PointObstacle : public Obstacle
{
public:
	Eigen::Vector2d position;
	void draw(Display*display, Window window, GC gc);
	PointObstacle(double x, double y);
	bool is_intersecting(Soldier& soldier) override;
	Eigen::Vector2d correction(Soldier& soldier) override;
};