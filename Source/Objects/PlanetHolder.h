#pragma once

#include <vector>
#include <memory>
#include <algorithm>

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


	bool handlePlanetSelecting(sf::Event e, const sf::RenderWindow& window);

	Planet* getOverlappingCursorPlanetPtr(const sf::RenderWindow& window);
};