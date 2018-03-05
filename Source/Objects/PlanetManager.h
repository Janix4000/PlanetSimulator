#pragma once

#include <vector>
#include <memory>
#include <algorithm>

#include "Planet.h"
#include "../Camera/Camera.h"

class PlanetManager
{
public:
	PlanetManager(Camera& mainCamera)
		:
		mainCamera(&mainCamera)
	{

	}

	void update(float dt)
	{
		refresh();
		attractAllPlanets();
		updateAllPlanets(dt);
		handlePlanetCrushing();
		refresh();
	}
	void render(sf::RenderTarget& renderer)const
	{
		for (const auto& planet : planets)
		{
			planet->render(renderer);
		}
	}
	void handleEvent(sf::Event e, const sf::RenderWindow& window)
	{
		switch (e.type)
		{
		case sf::Event::MouseButtonPressed:
			auto& newPlanet = *addPlanet();

			mainCamera->setTarget(newPlanet);

			auto mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
			newPlanet.setPosition({mousePos.x, mousePos.y});
			break;
		}
	}

	Planet* addPlanet()
	{
		auto planet = std::make_unique<Planet>();

		auto planetPtr = planet.get();

		planets.emplace_back(std::move(planet));
		return planetPtr;
	}

	void updateAllPlanets(float dt)
	{
		for (auto& planet : planets)
		{
			planet->update(dt);
		}
	}

	void attractAllPlanets()
	{
		for (int i = 0; i < planets.size(); i++)
		{
			auto& planet = planets[i];
			for (int j = i+1; j < planets.size(); j++)
			{
				auto& nextPlanet = planets[j];
				planet->attractBoth(*nextPlanet);
			}
		}
	}

	void handlePlanetCrushing()
	{
		for (int i = 0; i < planets.size(); i++)
		{
			auto& planet = planets[i];
			for (int j = i + 1; j < planets.size(); j++)
			{
				auto& nextPlanet = planets[j];
				if (nextPlanet->isOverlappingEnoughToMerge(*planet))
				{
					nextPlanet->consume(*planet);
					break;
				}
			}
		}
	}

	void refresh()
	{
		planets.erase(std::remove_if(planets.begin(), planets.end(), [](const auto& planet) {
			return !planet->isAlive();
		}), planets.end());
	}

private:
	std::vector<std::unique_ptr<Planet>> planets;

	Camera* mainCamera;
};