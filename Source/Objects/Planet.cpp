#include "Planet.h"

Planet::Planet()
	:
	circle(10.f),
	ID(planetsNum++)
{
	circle.setFillColor(getRandomColor());
}

void Planet::update(float dt)
{
	physic.update(dt);

	circle.setPosition(physic.pos);
}

void Planet::render(sf::RenderTarget & renderer) const
{
	renderer.draw(circle);
}

void Planet::attractBoth(Planet & other)
{
	auto forceVec = getForceVecBetween(other);

	applyForce(forceVec);
	other.applyForce(-forceVec);
}


void Planet::setMass(float newMass)
{
	mass = newMass;
	circle.setRadius(getNewRadiusByMass(newMass));
}

void Planet::setRadius(float newRadius)
{
	circle.setRadius(newRadius);
	mass = getNewMassByRadius(newRadius);
}

void Planet::setPosition(const Vec2 & newPosition)
{
	physic.pos = newPosition;
	circle.setPosition(newPosition);
}


size_t Planet::planetsNum = 0u;