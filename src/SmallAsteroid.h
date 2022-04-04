#pragma once

#include "AbstractAsteroidBase.h"

class SmallAsteroid : public AbstractAsteroidBase
{
public:
	SmallAsteroid(Vector position, Vector velocity, SDL_Renderer* renderer);

	void render(SDL_Renderer* renderer) override;
	void onHit(std::vector<AbstractAsteroidBase*>& asteroids, SDL_Renderer* renderer) override;
	Vector getPosition() override;
	void setX(float x) override;
	void setY(float y) override;
};