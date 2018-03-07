#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include <cassert>

#include "../Camera/Camera.h"

class PlanetHolder
{
private:
	enum class State
	{
		Running,
		Editing,
		Pause
	};

public:
	PlanetHolder();

	void update(float dt);

	

	void render(sf::RenderTarget& renderer)const;

	void handleEvent(sf::Event e, const sf::RenderWindow& window);

	void handleInput(const sf::RenderWindow& window);

	Planet* addPlanet();

	bool isSelected(const Planet& planet) const;
	bool isAnySelected() const;

	Planet* getSelectedPlanetPtr();

	void unSelect();

	void refresh();

private:
	std::vector<std::unique_ptr<Planet>> planets;

	Planet* selectedPlanet{ nullptr };

	void updateAllPlanets(float dt);

	void attractAllPlanets();

	void handlePlanetCrushing();

	void selectPlanet(Planet& planet);

	Planet& getNextPlanet(const Planet& previousPlanet)
	{
		const int prevID = previousPlanet.getID();


	}

	/*
	Planet& getNextPlanetByID(const int prevID)
	{
		assert(!planets.empty());

		int nextID = 10000; //xd

		Planet* nextPlanet = { nullptr };

		for (const auto& planet : planets)
		{
			const int ID = planet->getID();
			if (ID > prevID)
			{
				if (ID < nextID && ID!=prevID)
				{
					nextID = ID;
					nextPlanet = planet.get();
				}
			}
		}

		if (nextPlanet == nullptr)
		{
			nextPlanet = planets.front().get();
			int minID = nextPlanet ->getID();

			for (const auto& planet : planets)
			{
				const int ID = planet->getID();
				if (ID < minID)
				{
					minID = ID;
					nextPlanet = planet.get();
				}
			}
		}
			return *nextPlanet;
	}

	Planet& getPreviousPlanetByID(const int nextID)
	{
		assert(!planets.empty());

		int prevID = -1; //xd

		Planet* prevPlanet = { nullptr };

		for (const auto& planet : planets)
		{
			const int ID = planet->getID();
			if (ID < nextID)
			{
				if (ID > prevID && ID != nextID)
				{
					prevID = ID;
					prevPlanet = planet.get();
				}
			}
		}

		if (prevPlanet == nullptr)
		{
			prevPlanet = planets.front().get();
			int minID = prevPlanet->getID();

			for (const auto& planet : planets)
			{
				const int ID = planet->getID();
				if (ID < minID)
				{
					minID = ID;
					prevPlanet = planet.get();
				}
			}
		}
		return *prevPlanet;
	}
	*/

	bool handlePlanetSelecting(sf::Event e, const sf::RenderWindow& window);

	Planet* getOverlappingCursorPlanetPtr(const sf::RenderWindow& window);
};