#pragma once

#include <vector>
#include <memory>
#include <algorithm>

#include "../Editor/PlanetEditor.h"
#include "../Camera/Camera.h"

#include "../Editor/Orbit.h"

class PlanetManager
{
private:
	enum class State
	{
		Running,
		Editing,
		Pause
	};

public:
	PlanetManager(Camera& mainCamera);

	void update(float dt);

	

	void render(sf::RenderTarget& renderer)const;

	void handleEvent(sf::Event e, const sf::RenderWindow& window);

	void handleInput(const sf::RenderWindow& window);

private:
	std::vector<std::unique_ptr<Planet>> planets;

	Camera* mainCamera;
	PlanetEditor editor;

	State state{ State::Pause };

	Planet* selectedPlanet{ nullptr };

	sf::RectangleShape run, pause, edit;

	void handleRunningEvent(sf::Event e, const sf::RenderWindow& window);

	void handleEditingEvent(sf::Event e, const sf::RenderWindow& window);

	void handlePauseEvent(sf::Event e, const sf::RenderWindow& window);

	void renderIcons(sf::RenderTarget& renderer) const;
	

	Planet* addPlanet();

	void updateEditor(float dt);

	void updateAllPlanets(float dt);

	void attractAllPlanets();

	void handlePlanetCrushing();

	void refresh();

	void startEditing(Planet& planet);

	void startEditingSelectedPlanet();

	void selectPlanet(Planet& planet);

	bool isSelected(const Planet& planet) const;

	Planet* getSelectedPlanetPtr();

	void unSelect();

	bool handlePlanetSelecting(sf::Event e, const sf::RenderWindow& window);

	Planet* getOverlappingCursorPlanetPtr(const sf::RenderWindow& window);

	void handleAddingEvent(sf::Event e, const sf::RenderWindow& window);

};