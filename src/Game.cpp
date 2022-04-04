#include <random>

#include "Game.h"
#include "BigAsteroid.h"
#include "SmallAsteroid.h"

#define PI 3.14159265

Game::Game(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	isRunning = true;
	window = nullptr;
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems Initialized!" << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
		{
			std::cout << "Window Created!" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			std::cout << "Renderer Created!" << std::endl;
		}

		isRunning = true;
	}

	player = new Player(Vector(width/2, height/2), this->renderer, "player.png");
	//asteroids.push_back(new BigAsteroid(Vector(400, 400), Vector(-2, -3), renderer));
}

void Game::update()
{
	std::random_device r;
	std::default_random_engine el(r());
	std::uniform_int_distribution<int> uniform_dist(0, 60 * 3);
	int num = uniform_dist(el);

	if (!num)
	{
		std::uniform_int_distribution<int> velDist(-20, 20);

		int b, x, y;

		b = std::uniform_int_distribution<int>(0, 1)(el);
		
		if (b)
		{
			x = std::uniform_int_distribution<int>(600, 800)(el);
		}
		else
		{
			x = std::uniform_int_distribution<int>(0, 200)(el);
		}

		b = std::uniform_int_distribution<int>(0, 1)(el);

		if (b)
		{
			y = std::uniform_int_distribution<int>(600, 800)(el);
		}
		else
		{
			y = std::uniform_int_distribution<int>(0, 200)(el);
		}

		asteroids.push_back(new BigAsteroid(Vector(x, y), Vector((float)velDist(el) / 10, (float)velDist(el) / 10), renderer));
	}

	player->updatePosition();

	for (auto& bullet : this->bullets)
	{
		if (bullet->getPosition().x < 0 - 4 || bullet->getPosition().x > 800 + 4 || bullet->getPosition().y < 0 - 4 || bullet->getPosition().y > 800 + 4)
		{
			bullets.erase(std::remove(bullets.begin(), bullets.end(), bullet), bullets.end());
			continue;
		}

		bullet->updatePosition();

		for (auto& asteroid : this->asteroids)
		{
			if (bullet->getPosition().x < asteroid->getPosition().x + asteroid->getSize() && bullet->getPosition().x + 4 > asteroid->getPosition().x && bullet->getPosition().y < asteroid->getPosition().y + asteroid->getSize() && bullet->getPosition().y + 4> asteroid->getPosition().y)
			{
				asteroid->onHit(this->asteroids, renderer);
				break;
			}
		}
	}

	for (auto& asteroid : this->asteroids)
	{
		asteroid->updatePosition();

		if (asteroid->getPosition().y < 0) asteroid->setY(800);
		if (asteroid->getPosition().y > 800) asteroid->setY(0);
		if (asteroid->getPosition().x < 0) asteroid->setX(800);
		if (asteroid->getPosition().x > 800) asteroid->setX(0);
	}
}

void Game::render()
{
	SDL_RenderClear(renderer);

	player->render(renderer);

	for (auto& asteroid : this->asteroids)
	{
		asteroid->render(renderer);
	}

	for (auto& bullet : this->bullets)
	{
		bullet->render(renderer);
	}

	SDL_RenderPresent(renderer);
}

void Game::handleEvents()
{

	SDL_Event event;

	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;

	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			isRunning = false;
			break;

		case SDLK_SPACE:
			bullets.push_back(new Bullet(player->getPosition(), Vector(sin(player->getAngle() * PI / 180), -cos(player->getAngle() * PI / 180)) * 8, renderer));
			break;

		}
	}

	const Uint8* keyState = SDL_GetKeyboardState(NULL);

	if (keyState[SDL_SCANCODE_RIGHT] || keyState[SDL_SCANCODE_D]) player->updateAngle(2);
	if (keyState[SDL_SCANCODE_LEFT] || keyState[SDL_SCANCODE_A]) player->updateAngle(-2);
	//if (keyState[SDL_SCANCODE_SPACE]) bullets.push_back(new Bullet(player->getPosition(), Vector(sin(player->getAngle() * PI / 180), -cos(player->getAngle() * PI / 180)) * 8, renderer, "bullet.png"));

	if (keyState[SDL_SCANCODE_UP] || keyState[SDL_SCANCODE_W])
	{
		player->updateAcceleration(0.05);
	}
	else
	{
		player->updateAcceleration(-0.05);
	}

}

Game::~Game()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}