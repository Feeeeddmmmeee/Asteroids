#include "Entity.h"

void Entity::updatePosition()
{
	this->position += this->velocity;
}

int Entity::getSize()
{
	return this->destRect.h;
}
