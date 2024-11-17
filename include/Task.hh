#pragma once
#include "Entity.hh"
class Task
{
public:
	static constexpr unsigned short error_tolerance=0;
	Entity *entity;
	enum {null,go} state=null;
	Eigen::Vector2d location;

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