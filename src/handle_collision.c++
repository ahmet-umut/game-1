#include "../include/functions.hh"
#include <iostream>
void handle_collision(Soldier& soldier, Obstacle* obstacle)
{
	if (obstacle->is_intersecting(soldier))	soldier.position = soldier.position + obstacle->correction(soldier);
}
void handle_collision(Soldier& soldier_a, Soldier& soldier_b)
{
	if (&soldier_a != &soldier_b)
	{
		double distance = soldier_a.distance(soldier_b);
		if (distance < 2 * Soldier::radius)
		{
			using namespace Eigen;
			Vector2d posdif01 = soldier_a.position +- soldier_b.position;
			soldier_b.position = soldier_b.position +- posdif01 / distance * (Soldier::radius - distance/2);
			soldier_a.position = soldier_a.position +  posdif01 / distance * (Soldier::radius - distance/2);
		}
	}
}

