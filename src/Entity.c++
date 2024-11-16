#include "../include/Entity.hh"
double Entity::distance(Entity& entity)
{
	return (entity.position - position).norm();
}