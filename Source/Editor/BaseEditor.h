#pragma once

#include <SFML\Graphics.hpp>

#include "../Objects/Planet.h"

#include <cassert>

class BaseEditor
{
protected:
using Key = sf::Keyboard::Key;
public:

	BaseEditor(Key key)
		:
		activeKey(key)
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
				std::cout << "is active\n";
			}
			break;
		case sf::Event::MouseButtonPressed:
			active = false;
			std::cout << "is inactive\n";
			break;
		default:
			break;
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

private:
	bool active;
	Planet* editingPlanet{nullptr};

	Key activeKey;
};