#pragma once

#include "BaseEditor.h"

class RadiusEditor
	:
	public BaseEditor
{
public:
	RadiusEditor(PlanetHolder& holder)
		:
		BaseEditor(Key::R, holder)
	{}

	void handleInput(const sf::RenderWindow& window) override
	{
		if (isActive())
		{
			auto mousePos = getRealMousePos(window);

			auto& planet = getPlanet();

			const auto radiusVec = mousePos - planet.getPosition();
			const float newRadius = radiusVec.getLen();

			planet.setRadius(newRadius);

			//std::cout << "setingVelocity\n";
		}
	}
};