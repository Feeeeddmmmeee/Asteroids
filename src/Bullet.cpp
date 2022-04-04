#include "Bullet.h"

Bullet::Bullet(Vector position, Vector velocity, SDL_Renderer* renderer)
{
	this->position = position;
	this->velocity = velocity;

	SDL_Surface* tempSurface = IMG_Load("res/gfx/bullet.png");
	this->texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
}

void Bullet::render(SDL_Renderer* renderer)
{
	this->destRect.h = this->destRect.w = 4;
	this->destRect.x = this->position.x;
	this->destRect.y = this->position.y;

	SDL_RenderCopy(renderer, this->texture, NULL, &this->destRect);
}

Vector Bullet::getPosition()
{
	return this->position;
}
