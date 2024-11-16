#pragma once
#include "xlib.hh"
#include "Soldier.hh"
class Obstacle
{
public:
	enum obsttype {point,line} type;
	virtual void draw(Display*display, Window window, GC gc)=0;
	virtual bool is_intersecting(Soldier& soldier)=0;
	virtual Eigen::Vector2d correction(Soldier& soldier)=0;
};