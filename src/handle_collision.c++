#include "../include/functions.hh"
void handle_collision(Soldier& soldier, Obstacle* obstacle)
{
	if (obstacle->is_intersecting(soldier))	soldier.position = soldier.position + obstacle->correction(soldier);
}
void handle_collision(Soldier& soldier_a, Soldier& soldier_b);