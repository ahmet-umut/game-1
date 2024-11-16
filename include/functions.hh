#pragma once
#include "Soldier.hh"
#include "Obstacle.hh"
void handle_collision(Soldier& soldier, Obstacle* obstacle);
void handle_collision(Soldier& soldier_a, Soldier& soldier_b);