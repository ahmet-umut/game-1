#pragma once
#include "Entity.hh"
class Task
{
public:
	static constexpr unsigned short error_tolerance=1;
	
	Entity *entity;
	enum {null,go,attack} state=null;
	Eigen::Vector2d location;
	Entity*target=nullptr;

	Task(Entity*entity) : entity(entity) {}
	void assess()
	{
		switch (state)
		{
		case go:
			if (entity->distance(location) < error_tolerance)	state=null;
			break;
		}
	}
};