#include "Game.h"

Game::Game()
	:
	window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "Planets"),
	planets(mainCamera),
	camSpeed(150.f)
{
	window.setFramerateLimit(60);
	mainCamera.setPosition({ WIN_WIDTH / 2.f, WIN_HEIGHT / 2.f });
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
		handleInput();

		dt = clock.restart().asSeconds();
	}
}

void Game::update(float dt)
{
	handleCameraInput(dt);
	mainCamera.applyToWindow(window);

	mainCamera.update(dt);

	planets.update(dt);
}

void Game::render()
{
	window.clear();
	
	planets.render(window);

	window.display();
}

void Game::handleEvent(sf::Event e)
{
	handleCameraEvent(e, window);
	planets.handleEvent(e, window);
}

void Game::handleInput()
{
	planets.handleInput(window);
}
