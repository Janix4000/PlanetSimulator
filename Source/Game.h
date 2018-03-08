#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>

#include "Camera\Camera.h"

#include "Objects/Planet/PlanetManager.h"

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
	float camZoomAddon{0.04f};

	void update(float dt);
	void render();
	void handleEvent(sf::Event e);
	void handleInput();

	void handleCameraInput(float dt)
	{
		Vec2 shift = { 0.f, 0.f };
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) shift.y -= camSpeed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) shift.y += camSpeed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) shift.x -= camSpeed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) shift.x += camSpeed;

		auto oldCamPos = mainCamera.getPosition();

		if(shift.getLenSq() > 0.f) mainCamera.move(shift * dt);

	}

	void handleCameraEvent(sf::Event e, const sf::RenderWindow& window)
	{
		switch (e.type)
		{
		case sf::Event::MouseWheelScrolled:

		{
			float delta = e.mouseWheelScroll.delta;
			if (delta < 0.f)
			{
				mainCamera.zoom(camZoomAddon);
			}
			else if (delta > 0.f)
			{
				mainCamera.zoom(-camZoomAddon);
			}
		}
			break;
		default:
			break;
		}
	}


	PlanetManager planets;
	Random<> rng;
};