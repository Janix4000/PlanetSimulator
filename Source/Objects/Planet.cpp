#include "Planet.h"

Planet::Planet()
	:
	circle(),
	ID(planetsNum++)
{
	setRadius(10.f);
	circle.setFillColor(getRandomColor());
}

sf::Color Planet::getRandomColor(int spacing) const
{
	Random<> rng;

	char newR = getRandomColorParameter(rng, spacing);
	char newG = getRandomColorParameter(rng, spacing);
	char newB = getRandomColorParameter(rng, spacing);

	return sf::Color(newR, newG, newB);
}

char Planet::getRandomColorParameter(Random<>& rng, int spacing) const
{
	int newColorParameter = rng.getIntInRange(0, 255 / spacing) * spacing;
	return char(newColorParameter);
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
	auto forceVec1 = getForceVecBetween(other);

	applyForce(forceVec1);

	auto forceVec2 = other.getForceVecBetween(*this);
	other.applyForce(forceVec2);
}

 Vec2 Planet::getForceVecBetween(const Planet & other)
{
	const auto distVec = getDistVecBetween(other);
	const float distSqr = distVec.getLenSq();

	if (distSqr < 10.f) return { 0.f, 0.f };

	float strength = G * mass * other.mass / distSqr;

	auto forceVec = distVec;
	forceVec.setLen(strength);

	return forceVec;
}

 Vec2 Planet::getDistVecBetween(const Planet & other) const
{
	return other.physic.pos - physic.pos;
}

 void Planet::applyForce(const Vec2 & force)
{
	physic.acc += force;
}


void Planet::setMass(float newMass)
{
	setRadius(getNewRadiusByMass(newMass));
}

float Planet::getNewRadiusByMass(float newMass) const
{
	return sqrt(newMass / PI);
}


void Planet::setRadius(float newRadius)
{
	circle.setRadius(newRadius);
	circle.setOrigin(newRadius, newRadius);
	mass = getNewMassByRadius(newRadius);
}

float Planet::getNewMassByRadius(float newRadius) const
{
	return pow(newRadius, 2) * PI;
}


void Planet::setPosition(const Vec2 & newPosition)
{
	physic.pos = newPosition;
	circle.setPosition(newPosition);
}

void Planet::setVelocity(const Vec2 & newVelocity)
{
	physic.vel = newVelocity;
}


size_t Planet::planetsNum = 0u;