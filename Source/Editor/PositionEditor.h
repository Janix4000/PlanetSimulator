#pragma once

#include "BaseEditor.h"

class PositionEditor
	:
	public BaseEditor
{
public:
	PositionEditor()
		:
		BaseEditor(Key::P)
	{}

	void handleInput(const sf::RenderWindow& window) override
	{
		if (isActive())
		{
			auto& planet = getPlanet();

			const auto newPos = getRealMousePos(window);
			planet.setPosition(newPos);

			std::cout << "X: " << newPos.x << " Y: " << newPos.y << "\n";
		}
	}
};