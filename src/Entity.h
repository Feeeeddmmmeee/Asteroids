#pragma once

#include "Vector.h"
#include "SDL_image.h"

class Entity
{
public:
	virtual void render(SDL_Renderer* renderer) = 0;
	virtual void updatePosition();
	int getSize();

protected:
	Vector position, velocity;
	SDL_Texture* texture;
	SDL_Rect destRect;

};