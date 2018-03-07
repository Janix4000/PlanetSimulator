#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>

#include "Camera\Camera.h"

#include "Editor\PlanetManager.h"

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
	void handleInput();

	void handleCameraControl(float dt)
	{
		Vec2 shift = { 0.f, 0.f };
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) shift.y -= camSpeed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) shift.y += camSpeed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) shift.x -= camSpeed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) shift.x += camSpeed;

		auto oldCamPos = mainCamera.getPosition();

		//std::cout << oldCamPos.x << " " << oldCamPos.y << "\n";

		if(shift.getLenSq() > 0.f) mainCamera.move(shift * dt);
	}


	PlanetManager planets;
	Random<> rng;
};