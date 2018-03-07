#pragma once

#include "BaseEditor.h"
#include "Orbit.h"

class OrbitEditor
	:
	public BaseEditor
{
public:

	OrbitEditor(PlanetHolder& holder)
		:
		BaseEditor(Key::O, holder)
	{}

	void handleInput(const sf::RenderWindow& window) override
	{
		if (isActive())
		{
			orbit.setOrbiterPos(getRealMousePos(window));
		}
	}

	void render(sf::RenderTarget& renderer) const override
	{
		if (isActive())
		{
			orbit.render(renderer);
		}
	}

	void update(float dt) override
	{
		if (isActive())
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
			{
				orbit.addToEFactor(dt);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
			{
				orbit.addToEFactor(-dt);
			}			
		}
	}

private:

	void init() override
	{
		orbit.setSun(getPlanet());

		auto& newOrbiter = addPlanet();

		const float sunRadius = getPlanet().getRadius();
		float newRadius = sunRadius / 4.f;

		newOrbiter.setRadius(newRadius);
		orbit.setOrbiter(newOrbiter);
	}

	void end() override
	{
		orbit.free();
	}

	Orbit orbit;
};