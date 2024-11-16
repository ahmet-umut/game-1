#pragma once
#include "Entity.hh"
#include "Trajectile.hh"
#include "xlib.hh"
#include <eigen3/Eigen/Core>
class Soldier : public Entity
{
public:
	static inline Soldier*selsoldier=nullptr;
	static constexpr double radius = 11;
	Eigen::Vector2d velocity = {0,0};	double direction = 0;
	Trajectile*trajectile;

	Soldier(float x, float y);
	void draw(Display*display, Window window, GC gc);
	void execute();
	void select();
	bool is_around(double x, double y);
};