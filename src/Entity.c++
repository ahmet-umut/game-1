#include "../include/Entity.hh"
#include <iostream>

void Entity::draw(Display*display, Window window, GC gc) {
	std::cout << "Entity drawing!" << std::endl;
}

void Entity::attack() {
	std::cout << "Entity attacking!" << std::endl;
}