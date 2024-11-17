#pragma once
#include "Combatant.hh"
#include "xlib.hh"
#include <eigen3/Eigen/Dense>
#include <deque>
class Polybolos : public Combatant
{
public:
	unsigned char cooldown;

	void draw(Display*display, Window window, GC gc);
	void execute();
	bool is_around(double x, double y) override;
	using Combatant::is_around;

	using Combatant::Combatant;
	Projectile fire();
};