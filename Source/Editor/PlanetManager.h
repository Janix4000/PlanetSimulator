#pragma once

#include "../Editor/PlanetEditor.h"

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

	PlanetManager(Camera& cam);

	void update(float dt);

	void render(sf::RenderTarget& renderer)const;

	void handleEvent(sf::Event e, const sf::RenderWindow& window);

	void handleInput(const sf::RenderWindow& window);

private:
	Camera * mainCamera;

	PlanetHolder holder;

	PlanetEditor editor;

	State state{ State::Pause };

	sf::CircleShape run, pause, edit;

	void updateEditor(float dt);

	void updatePlanets(float dt);

	void handleRunningEvent(sf::Event e, const sf::RenderWindow& window);

	void handleEditingEvent(sf::Event e, const sf::RenderWindow& window);

	void handlePauseEvent(sf::Event e, const sf::RenderWindow& window);

	void renderIcons(sf::RenderTarget& renderer) const;


	void startEditing(Planet& planet);

	void startEditingClickedPlanet();

	void handleAddingEvent(sf::Event e, const sf::RenderWindow& window);

	void handleDeleteEvent(sf::Event e, const sf::RenderWindow& window);

	void deleteEdited();

	void changeStateToPause()
	{
		state = State::Pause;
		mainCamera->free();
	}
};