#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include <cassert>

#include "../../Camera/Camera.h"

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

	bool isSelectedRemoved()const;

	void refresh();

	void selectNextPlanet();

	void selectPreviousPlanet();

	bool isReadyToCamFollow() const;

	void removeReadyToCamMark();

	bool isClicked()const;

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