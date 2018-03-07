#include "PlanetHolder.h"

PlanetHolder::PlanetHolder()
{
	
}


void PlanetHolder::update(float dt)
{
	refresh();
	updateAllPlanets(dt);
}


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
	planets.erase(std::remove_if(planets.begin(), planets.end(), [](const auto& planet) {
		return !planet->isAlive();
	}), planets.end());
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

	planets.emplace_back(std::move(planet));
	return planetPtr;
}


void PlanetHolder::selectPlanet(Planet & planet)
{
	selectedPlanet = &planet;
}

bool PlanetHolder::isSelected(const Planet & planet) const { return selectedPlanet == &planet; }

bool PlanetHolder::isAnySelected() const
{
	return selectedPlanet != nullptr;
}

Planet * PlanetHolder::getSelectedPlanetPtr() { return selectedPlanet; }

void PlanetHolder::unSelect()
{
	selectedPlanet = nullptr;
}

bool PlanetHolder::handlePlanetSelecting(sf::Event e, const sf::RenderWindow & window)
{
	if (e.type == sf::Event::MouseButtonPressed)
	{
		auto clicked = getOverlappingCursorPlanetPtr(window);
		if (clicked != nullptr)
		{
			selectPlanet(*clicked);
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



