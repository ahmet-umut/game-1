#include "../include/functions.hh"
void handle_collision(Soldier& soldier, Obstacle* obstacle)
{
	if (obstacle->is_intersecting(soldier))	soldier.position = soldier.position + obstacle->correction(soldier);
}
void handle_collision(Soldier& soldier_a, Soldier& soldier_b)
{
	if (soldier_a.distance(soldier_b) < 2 * Soldier::radius)
		{
			using namespace Eigen;
			Vector2d posdif01 = soldier_b.position - soldier_a.position;
			soldier_a.position = soldier_a.position + posdif01 / posdif01.norm() * (Soldier::radius - posdif01.norm()/2);
			soldier_b.position = soldier_b.position - posdif01 / posdif01.norm() * (Soldier::radius - posdif01.norm()/2);
		}
}