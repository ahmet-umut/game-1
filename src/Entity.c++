#include "../include/Entity.hh"
#include <iostream>
void Entity::draw() {
	std::cout << "Drawing entity at (" << x << ", " << y << ")" << std::endl;
}

void Entity::attack() {
	std::cout << "Entity attacking!" << std::endl;
}