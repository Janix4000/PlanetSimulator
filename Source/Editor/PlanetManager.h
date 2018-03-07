#pragma once
#include"../Objects/PlanetHolder.h"

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

	void unselect();

	void renderIcons(sf::RenderTarget& renderer) const;


	void startEditing(Planet& planet);

	void startEditingSelectedPlanet();

	void handleAddingEvent(sf::Event e, const sf::RenderWindow& window);
};