#include "Player.h"
#include <math.h>

#define PI 3.14159265

Player::Player(Vector position, SDL_Renderer* renderer, const char* fileName)
{
	this->position = position;
	this->velocity = Vector(0, 0);
	this->angle = 0;
	this->speed = 0;

	SDL_Surface* tempSurface = IMG_Load("res/gfx/player.png");
	this->texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
}

void Player::render(SDL_Renderer* renderer)
{
	this->destRect.h = this->destRect.w = 32;
	this->destRect.x = this->position.x - 16;
	this->destRect.y = this->position.y - 16;

	//SDL_RenderCopy(renderer, this->texture, NULL, &this->destRect);
	SDL_RenderCopyEx(renderer, this->texture, NULL, &this->destRect, this->angle, NULL, SDL_FLIP_NONE);
}

void Player::updatePosition()
{
	this->speed += this->acceleration;

	if (this->speed < 0) this->speed = 0;
	if (this->speed > 5) this->speed = 5;

	this->velocity = Vector(sin(this->angle * PI / 180), -cos(this->angle * PI / 180)) * this->speed;

	if (this->position.y < 0) this->position.y = 800;
	if (this->position.y > 800) this->position.y = 0;
	if (this->position.x < 0) this->position.x = 800;
	if (this->position.x > 800) this->position.x = 0;

	this->position += this->velocity;
}

void Player::updateAngle(double a)
{
	this->angle += a;
}

void Player::updateAcceleration(float acceleration)
{
	this->acceleration = acceleration;
}

Vector Player::getPosition()
{
	return this->position;
}

float Player::getAngle()
{
	return this->angle;
}
