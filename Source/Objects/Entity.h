#pragma once

#include "Component.h"

class Entity
{
public:

	virtual void update(float dt) noexcept {}

	virtual void render(sf::RenderTarget& renderer) const noexcept {}

	virtual void handleEvent(sf::Event e, const sf::RenderWindow& window) noexcept {}

	virtual ~Entity() noexcept {}

private:

	bool alive = true;

public:
	bool isAlive() const
	{
		return alive;
	}
};