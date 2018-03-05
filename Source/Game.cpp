#include "Game.h"

Game::Game()
	:
	window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "Planets")
{
	window.setFramerateLimit(60);


	planet1.setPosition({ 100.f, 100.f });
	planet2.setPosition({ 300.f, 400.f });

	planet1.setVelocity({ 20.f, -10.f });
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
	planet1.attractBoth(planet2);

	planet1.update(dt);
	planet2.update(dt);
}

void Game::render()
{
	window.clear();

	planet1.render(window);
	planet2.render(window);

	window.display();
}

void Game::handleEvent(sf::Event e)
{
}
