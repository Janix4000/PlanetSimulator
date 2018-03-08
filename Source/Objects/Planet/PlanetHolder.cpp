#include "PlanetHolder.h"

PlanetHolder::PlanetHolder()
{
	
}


void PlanetHolder::update(float dt)
{
	refresh();
	updateAllPlanets(dt);
}


void PlanetHolder::selectPreviousPlanet()
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

bool PlanetHolder::isReadyToCamFollow() const
{
	return readyToCamFollow;
}

void PlanetHolder::removeReadyToCamMark()
{
	readyToCamFollow = false;
}

bool PlanetHolder::isClicked() const { return clicked; }

void PlanetHolder::updateAllPlanets(float dt)
{
	attractAllPlanets();
	for (auto& planet : planets)
	{
		planet->update(dt);
	}
	handlePlanetCrushing();
	refresh();
}

void PlanetHolder::attractAllPlanets()
{
	for (size_t i = 0u; i < planets.size(); i++)
	{
		auto& planet = planets[i];
		for (size_t j = i + 1; j < planets.size(); j++)
		{
			auto& nextPlanet = planets[j];
			planet->attractBoth(*nextPlanet);
		}
	}
}

void PlanetHolder::handlePlanetCrushing()
{
	for (size_t i = 0u; i < planets.size(); i++)
	{
		auto& planet = planets[i];
		for (size_t j = i + 1; j < planets.size(); j++)
		{
			auto& nextPlanet = planets[j];
			if (nextPlanet->isOverlappingEnoughToMerge(*planet))
			{
				if (isSelected(*planet)) selectPlanet(*nextPlanet);
				nextPlanet->consume(*planet);
				break;
			}
		}
	}
}

void PlanetHolder::refresh()
{
	//readyToCamFollow = false;

	auto newEnd = std::remove_if(planets.begin(), planets.end(), [](const auto& planet) {
		return !planet->isAlive();
	});

	const bool selectedLives = std::any_of(planets.begin(), newEnd, [&](const auto& planet) {
		return planet.get() == selectedPlanet;
	});

	if (!selectedLives)
	{
		if (newEnd != planets.begin())
		{
			selectedPlanet = planets.front().get();
		}
		else
		{
			selectedPlanet = nullptr;
		}

		selectedWasRemoved = true;
	}

	planets.erase(newEnd, planets.end());
}

void PlanetHolder::selectNextPlanet()
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


void PlanetHolder::render(sf::RenderTarget & renderer) const
{
	for (const auto& planet : planets)
	{
		planet->render(renderer);
	}
}



void PlanetHolder::handleInput(const sf::RenderWindow & window)
{
}

void PlanetHolder::handleEvent(sf::Event e, const sf::RenderWindow & window)
{
	handlePlanetSelecting(e, window);
}


Planet * PlanetHolder::addPlanet()
{
	auto planet = std::make_unique<Planet>();
	auto planetPtr = planet.get();

	selectPlanet(*planet);

	planets.emplace_back(std::move(planet));
	return planetPtr;
}

Planet * PlanetHolder::addAndSelectPlanet()
{
	auto* newPlanet = addPlanet();

	selectPlanet(*newPlanet);

	return newPlanet;
}




bool PlanetHolder::isSelected(const Planet & planet) const { return selectedPlanet == &planet; }

bool PlanetHolder::isAnySelected() const
{
	return selectedPlanet != nullptr;
}

Planet& PlanetHolder::getSelectedPlanet()

{ 
	assert(selectedPlanet != nullptr);
	return *selectedPlanet;
}

bool PlanetHolder::isSelectedRemoved() const
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

bool PlanetHolder::handlePlanetSelecting(sf::Event e, const sf::RenderWindow & window)
{
	clicked = false;
	if (e.type == sf::Event::MouseButtonPressed)
	{
		auto clickedOne = getOverlappingCursorPlanetPtr(window);

		if (clickedOne != nullptr)
		{
			clicked = true;
			selectPlanet(*clickedOne);
			return true;
		}
	}
	return false;
}

Planet * PlanetHolder::getOverlappingCursorPlanetPtr(const sf::RenderWindow & window)
{
	const auto mousePos = getRealMousePos(window);

	auto overlapper = std::find_if(planets.begin(), planets.end(), [&](std::unique_ptr<Planet>& planet) {
		return planet->isOverlappingPoint(mousePos);
	});

	if (overlapper == planets.end()) return nullptr;

	return overlapper->get();
}

void PlanetHolder::selectPlanet(Planet & planet)
{
	selectedPlanet = &planet;
}

