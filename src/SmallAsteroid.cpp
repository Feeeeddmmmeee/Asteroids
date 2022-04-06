#include "SmallAsteroid.h"
#include <random>

SmallAsteroid::SmallAsteroid(Vector position, Vector velocity, SDL_Renderer* renderer)
{
	this->position = position;
	this->velocity = velocity;

	std::random_device r;
	std::default_random_engine el(r());
	std::uniform_int_distribution<int> uniform_dist(0, 360);
	this->angle = uniform_dist(el);
	

	SDL_Surface* tempSurface = IMG_Load("res/gfx/asteroid1.png");
	this->texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
}

void SmallAsteroid::render(SDL_Renderer* renderer)
{
	this->destRect.h = this->destRect.w = 32;
	this->destRect.x = this->position.x;
	this->destRect.y = this->position.y;

	SDL_RenderCopyEx(renderer, this->texture, NULL, &this->destRect, this->angle, NULL, SDL_FLIP_NONE);
}

void SmallAsteroid::onHit(std::vector<AbstractAsteroidBase*>& asteroids, SDL_Renderer* renderer)
{
	asteroids.erase(std::remove(asteroids.begin(), asteroids.end(), this), asteroids.end());
}

Vector SmallAsteroid::getPosition()
{
	return this->position;
}

void SmallAsteroid::setX(float x)
{
	this->position.x = x;
}

void SmallAsteroid::setY(float y)
{
	this->position.y = y;
}
