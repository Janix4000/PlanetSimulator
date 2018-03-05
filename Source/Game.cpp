#include "Game.h"

Game::Game()
	:
	window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "Planets")
{
	window.setFramerateLimit(60);
}

void Game::run()
{
	sf::Clock clock;
	float dt = 1.f/60.f;

	while (window.isOpen())
	{
		sf::Event e;
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed) window.close();

			handleEvent(e);
		}

		update(dt);
		render();

		dt = clock.restart().asSeconds();
	}
}

void Game::update(float dt)
{
}

void Game::render()
{
	window.clear();

	window.display();
}

void Game::handleEvent(sf::Event e)
{
}
