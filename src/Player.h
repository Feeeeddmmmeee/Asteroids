#pragma once

#include "Entity.h"

class Player : public Entity
{
public:
	Player(Vector position, SDL_Renderer* renderer, const char* fileName);
	void render(SDL_Renderer* renderer) override;
	void updatePosition() override;
	void updateAngle(double a);
	void updateAcceleration(float acceleration);
	
	Vector getPosition();
	float getAngle();

private:
	float angle, speed, acceleration;

};