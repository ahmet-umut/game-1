module;
#include <iostream>
export module collisions;
import soldier;
#include "../include/Obstacle.hh"
export void handle_collision(Soldier& soldier_a, Soldier& soldier_b)
{
	std::cout << "Handling collision between soldiers" << std::endl;
}
export void handle_collision(Soldier& soldier, Obstacle* obstacle)
{
	std::cout << "Handling collision between soldier and point obstacle" << std::endl;
}