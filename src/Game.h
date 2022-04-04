#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "AbstractAsteroidBase.h"
#include "Player.h"
#include "Bullet.h"

#include <iostream>
#include <vector>

class Game {

public:
	Game(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	~Game();

	void update();
	void render();
	void handleEvents();

	bool running() { return isRunning; };

private:
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;

	std::vector<AbstractAsteroidBase*> asteroids;
	std::vector<Bullet*> bullets;
	Player* player;
};