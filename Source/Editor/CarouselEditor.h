#pragma once

#include "BaseEditor.h"

class CarouselEditor
	:
	public BaseEditor
{
public:
	CarouselEditor(PlanetHolder& holder)
		:
		BaseEditor(Key::C, holder)
	{}

	void handleInput(const sf::RenderWindow& window) override
	{
		if (isActive())
		{
			calcCarousel(window);
		}
	}

private:

	std::vector<Planet*> orbiters;

	void holdAdditionalEvents(sf::Event e, const sf::RenderWindow& window) override
	{
		switch (e.type)		
		{
		case sf::Event::KeyPressed:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
			{
				if (orbiters.size() < 15u)
				{
					addOrbiter();
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
			{
				if (orbiters.size() > 1u)
				{
					removeLastOrbiter();
				}
			}
			break;
		default:
			break;
		}
	}

	void addOrbiter()
	{
		auto& orbiter = addPlanet();
		orbiter.setRadius(getPlanet().getRadius() / 8.f);
		orbiters.emplace_back(&orbiter);
	}

	void removeLastOrbiter()
	{
		removePlanet(*orbiters.back());
		orbiters.pop_back();
	}

	void calcCarousel(const sf::RenderWindow& window)
	{
		const auto& sun = getPlanet();
		float sunMass = sun.getMass();
		const auto basePos = sun.getPosition();
		const auto baseVel = sun.getVelocity();

		auto shift = getRealMousePos(window) - sun.getPosition();

		const float dist = shift.getLen();

		float rotation = TWO_PI / float(orbiters.size());
		float baseAngle = shift.getAngleBetween({ 0.f, 1.f });

		float speed = sqrt(sunMass*G / (dist));


		for (size_t i = 0u; i < orbiters.size(); i++)
		{
			float x = dist * cos(rotation * float(i) + baseAngle);
			float y = dist * sin(rotation * float(i) + baseAngle);

			const Vec2 pos = { x, y };

			auto velocity = pos.getPerpendicular();
			velocity.setLen(speed);

			orbiters[i]->setPosition(pos + basePos);
			orbiters[i]->setVelocity(velocity + baseVel);
		}
	}

	void init() override
	{
		addOrbiter();
		addOrbiter();
		//addOrbiter();
	}

	void end() override
	{
		orbiters.clear();
	}
};
