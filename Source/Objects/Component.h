#pragma once

#include <SFML/Graphics.hpp>

class Entity;

class Component
{
public:

	virtual void update(float dt) noexcept {}

	virtual void render(sf::RenderTarget& renderer) const noexcept {}

	virtual void handleEvent(sf::Event e, const sf::RenderWindow& window) noexcept {}

	virtual void init() noexcept {}

	virtual ~Component() noexcept {}

	Entity * holder = nullptr;
};