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

	Planet* addAndSelectPlanet();

	bool isSelected(const Planet& planet) const;
	bool isAnySelected() const;

	Planet& getSelectedPlanet();

	bool isSelectedRemoved()const
	{
		if (selectedWasRemoved)
		{
			selectedWasRemoved = false;
			return true;
		}
		else
		{
			return false;
		}
	}

	void refresh();

	void selectNextPlanet()
	{
		readyToCamFollow = false;

		if (planets.size() > 0u)
		{
			if (selectedPlanet == nullptr)
			{
				selectPlanet(*(planets.front()));
			}
			else
			{
					Planet* nextPlanet = { nullptr };

					const int oldID = selectedPlanet->getID();

					int newID = 10000;

					for (const auto& planet : planets)
					{
						int ID = planet->getID();

						if (ID > oldID)
						{
							if (ID < newID)
							{
								newID = ID;
								nextPlanet = planet.get();
							}
						}
					}

					if (nextPlanet == nullptr)
					{
						newID = selectedPlanet->getID();
						for (const auto& planet : planets)
						{
							int ID = planet->getID();
							if (ID <= newID)
							{
								newID = ID;
								nextPlanet = planet.get();
							}
						}
					}

					readyToCamFollow = true;
					selectPlanet(*nextPlanet);
			}
		}

		readyToCamFollow = true;
	}

	void selectPreviousPlanet()
	{
		readyToCamFollow = false;

		if (planets.size() > 0u)
		{
			if (selectedPlanet == nullptr)
			{
				selectPlanet(*(planets.front()));
			}
			else
			{
				Planet* prevoiusPlanet = { nullptr };

				const int oldID = selectedPlanet->getID();

				int newID = -1;

				for (const auto& planet : planets)
				{
					int ID = planet->getID();

					if (ID < oldID)
					{
						if (ID > newID)
						{
							newID = ID;
							prevoiusPlanet = planet.get();
						}
					}
				}

				if (prevoiusPlanet == nullptr)
				{
					newID = selectedPlanet->getID();
					for (const auto& planet : planets)
					{
						int ID = planet->getID();
						if (ID >= newID)
						{
							newID = ID;
							prevoiusPlanet = planet.get();
						}
					}
				}

				readyToCamFollow = true;
				selectPlanet(*prevoiusPlanet);
			}
		}

		readyToCamFollow = true;
	}

	bool isReadyToCamFollow() const
	{
		return readyToCamFollow;
	}

	bool isClicked()const { return clicked; }

private:
	std::vector<std::unique_ptr<Planet>> planets;

	Planet* selectedPlanet{ nullptr };



	mutable bool selectedWasRemoved{ false };

	bool readyToCamFollow{ false };
	bool clicked{ false };



	void updateAllPlanets(float dt);

	void attractAllPlanets();

	void handlePlanetCrushing();

	void selectPlanet(Planet& planet);

	bool handlePlanetSelecting(sf::Event e, const sf::RenderWindow& window);

	Planet* getOverlappingCursorPlanetPtr(const sf::RenderWindow& window);

};