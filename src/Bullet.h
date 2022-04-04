#pragma once

#include "Entity.h"

class Bullet : public Entity
{
public:
	Bullet(Vector position, Vector velocity, SDL_Renderer* renderer);
	void render(SDL_Renderer* renderer) override;
	Vector getPosition();

};