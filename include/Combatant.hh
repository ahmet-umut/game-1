#pragma once
#include "Projectile.hh"
#include "Task.hh"
#include <unordered_map>
class Combatant : public Entity
{
public:
	static inline Combatant*selected_combatant=nullptr;
	Task task;
	std::unordered_multimap<Combatant*,Projectile*>* projectiles=nullptr;

	Combatant(std::unordered_multimap<Combatant*,Projectile*>* projectiles, double x,double y) : Entity(x,y), task(this), projectiles(projectiles) {}

	Combatant* select(Eigen::Vector2d clicked_position)
	{
		if (is_around(clicked_position))	return this;
		return nullptr;
	}
	virtual bool is_around(double x, double y)=0;
	bool is_around(Eigen::Vector2d point)
	{
		return is_around(point.x(), point.y());
	}
};