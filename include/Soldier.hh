#pragma once
#include "Combatant.hh"
#include "xlib.hh"
#include <eigen3/Eigen/Core>
class Soldier : public Combatant
{
public:
	static constexpr double radius = 11;
	Eigen::Vector2d velocity = {0,0};

	Soldier(std::unordered_multimap<Combatant*,Projectile*>* projectiles, double x, double y);

	void draw(Display*display, Window window, GC gc);
	void execute();

	using Combatant::is_around;
	bool is_around(double x, double y) override;
};