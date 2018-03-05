#pragma once

#include <SFML/Graphics.hpp>

#include "Camera\Camera.h"

#include "Objects\Planet.h"

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720

class Game
{
public:
	Game();

	void run();



private:
	sf::RenderWindow window;

	Camera mainCamera;
	float camSpeed;

	void update(float dt);
	void render();
	void handleEvent(sf::Event e);

	void handleCameraControl(float dt)
	{
		sf::Vector2f shift;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) shift.x += camSpeed * dt;
	}


	Planet planet1;
	Planet planet2;

};