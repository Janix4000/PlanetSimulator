#pragma once

#include <SFML\Graphics.hpp>

#include "../Objects/Planet/PlanetHolder.h"

#include <cassert>

class BaseEditor
{
protected:
using Key = sf::Keyboard::Key;
public:

	BaseEditor(Key key, PlanetHolder& holder)
		:
		activeKey(key),
		holder(&holder)
	{}

	virtual void update(float dt) {}

	virtual void render(sf::RenderTarget& renderer) const {}

	virtual void handleInput(const sf::RenderWindow& window) {}

	void handleEvent(sf::Event e, const sf::RenderWindow& window)
	{
		switch (e.type)
		{
		case sf::Event::KeyPressed:
			if (sf::Keyboard::isKeyPressed(activeKey))
			{
				active = true;
				init();
			}
			break;
		case sf::Event::MouseButtonPressed:
			active = false;
			end();
			break;
		default:
			break;
		}

		if (isActive())
		{
			holdAdditionalEvents(e, window);
		}
	}

	bool isActive() const { return active; }
	void setNewTarget(Planet& target)
	{
		editingPlanet = &target;
	}
	void freePlanet()
	{
		editingPlanet = nullptr;
		active = false;
	}

protected:
	Planet & getPlanet()
	{
		assert(editingPlanet != nullptr);
		return *editingPlanet;
	}

	Planet& addPlanet()
	{
		auto& newPlanet = *(holder->addPlanet());

		holder->isAnySelected();

		return (newPlanet);
	}

	void removePlanet(Planet& planet)
	{
		planet.kill();
		holder->refresh();
	}

	virtual void init() {}
	virtual void end() {}
	virtual void holdAdditionalEvents(sf::Event e, const sf::RenderWindow& window) {}

private:
	bool active;
	Planet* editingPlanet{nullptr};

	PlanetHolder* holder;

	Key activeKey;
};