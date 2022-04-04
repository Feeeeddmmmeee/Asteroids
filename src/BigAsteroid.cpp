#include "BigAsteroid.h"
#include "SmallAsteroid.h"

BigAsteroid::BigAsteroid(Vector position, Vector velocity, SDL_Renderer* renderer)
{
	this->position = position;
	this->velocity = velocity;

	SDL_Surface* tempSurface = IMG_Load("res/gfx/asteroid0.png");
	this->texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
}

void BigAsteroid::render(SDL_Renderer* renderer)
{

	this->destRect.h = this->destRect.w = 64;
	this->destRect.x = this->position.x;
	this->destRect.y = this->position.y;

	SDL_RenderCopy(renderer, this->texture, NULL, &this->destRect);
}

void BigAsteroid::onHit(std::vector<AbstractAsteroidBase*>& asteroids, SDL_Renderer* renderer)
{
	asteroids.push_back(new SmallAsteroid(this->position, this->velocity, renderer));
	asteroids.push_back(new SmallAsteroid(this->position, this->velocity * -1, renderer));

	asteroids.erase(std::remove(asteroids.begin(), asteroids.end(), this), asteroids.end());
}

Vector BigAsteroid::getPosition()
{
	return this->position;
}


void BigAsteroid::setX(float x)
{
	this->position.x = x;
}

void BigAsteroid::setY(float y)
{
	this->position.y = y;
}
