#include "../include/Entity.hh"
double Entity::distance(Eigen::Vector2d point)
{
	return (point - position).norm();
}
double Entity::distance(Entity& entity)
{
	return distance(entity.position);
}