#pragma once

#include "BaseEditor.h"

class VelocityEditor
	:
	public BaseEditor
{
public:
	VelocityEditor(PlanetHolder& holder)
		:
		BaseEditor(Key::V, holder)
	{}

	void handleInput(const sf::RenderWindow& window) override
	{
		if (isActive())
		{
			auto mousePos = getRealMousePos(window);

			auto& planet = getPlanet();

			const auto newVel = mousePos - planet.getPosition();
			planet.setVelocity(newVel);

			//std::cout << "setingVelocity\n";
		}
	}
};