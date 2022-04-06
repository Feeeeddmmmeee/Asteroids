#pragma once

#include "Entity.h"
#include <vector>

class AbstractAsteroidBase : public Entity
{
public:
	virtual void render(SDL_Renderer* renderer) = 0;
	virtual void onHit(std::vector<AbstractAsteroidBase*>& asteroids, SDL_Renderer* renderer) = 0;
	virtual Vector getPosition() = 0;
	virtual void setX(float x) = 0;
	virtual void setY(float y) = 0;

protected:
	float angle;
};