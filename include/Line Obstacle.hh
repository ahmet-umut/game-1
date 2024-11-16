#pragma once
#include "xlib.hh"
#include "Obstacle.hh"
#include "Line Segment.hh"
class LineObstacle: public Obstacle
{
public:
	LineSegment lineSegment;
	void draw(Display*display, Window window, GC gc) override;
	LineObstacle();
	LineObstacle(double x1, double y1, double x2, double y2);
	bool is_intersecting(Soldier& soldier) override;
	Eigen::Vector2d correction(Soldier& soldier) override;
};