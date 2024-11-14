#pragma once
#include "soldier.hh"
class Obstacle
{
public:
	enum obsttype {point,line} type;	//0 for point, 1 for line

	//Obstacle(obsttype type) : type(type) {}

	virtual bool isintersecting(Soldier&) = 0;
	virtual Vector correction(Soldier&) = 0;
};