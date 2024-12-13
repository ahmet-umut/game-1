#pragma once
#include <eigen3/Eigen/Dense>
#include "Soldier.hh"
#include "Obstacle.hh"
#include "Projectile.hh"
#include "Polybolos.hh"
#include "../include/gamestate.hh"
#include <deque>
void handle_collision(Soldier& soldier, Obstacle* obstacle);
void handle_collision(Soldier& soldier_a, Soldier& soldier_b);
gamestate handle_next_event(gamestate state, Display* display, std::deque<Soldier>& soldiers, std::deque<Polybolos>& polybolos, bool* test_flag);