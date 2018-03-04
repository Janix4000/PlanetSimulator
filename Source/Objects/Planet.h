#pragma once

#include "Entity.h"
#include "FreePhysics.h"

#include "../Utilities/Vec2.h"
#include "../Utilities/Random.h"

#define G 10.f

class Planet
{
public:

	Planet();

	void update(float dt);
	void render(sf::RenderTarget& renderer) const;
	
	void attractBoth(Planet& other);
	void attractTo(const Vec2& attractorPos);

	size_t getID() const { return ID; }

	float getRadius() const { return circle.getRadius(); }
	float getMass() const { return mass; }

	void setMass(float newMass);
	void setRadius(float newRadius);

	void setPosition(const Vec2& newPosition);
	void setVelocity(const Vec2& newVelocity);

	void kill() { alive = false; }

private:
	FreePhysics physic;

	float mass;
	sf::Color color;
	sf::CircleShape circle;

	bool alive = true;

	const size_t ID;
	static size_t planetsNum;

private:

	float getNewRadiusByMass(float newMass) const
	{
		return sqrt(newMass / PI);
	}

	float getNewMassByRadius(float newRadius) const
	{
		return pow(newRadius, 2) * PI;
	}

	sf::Color getRandomColor(int spacing = 16) const
	{
		Random<> rng;

		char newR = getRandomColorParameter(rng, spacing);
		char newG = getRandomColorParameter(rng, spacing);
		char newB = getRandomColorParameter(rng, spacing);

		return sf::Color( newR, newG, newB );
	}

	char getRandomColorParameter(Random<>& rng, int spacing = 1) const
	{
		int newColorParameter = rng.getIntInRange(0, 255 / spacing) * spacing;
		return char(newColorParameter);
	}


	Vec2 getForceVecBetween(const Planet& other)
	{
		const auto distVec = getDistVecBetween(other);
		const float distSqr = distVec.getLenSq();

		if (distSqr < 10.f) return { 0.f, 0.f };

		float strength = G * mass * other.mass / distSqr;

		auto forceVec = distVec;
		forceVec.setLen(strength);

		return forceVec;
	}

	Vec2 getDistVecBetween(const Planet& other)
	{
		return other.physic.pos - physic.pos;
	}

	void applyForce(const Vec2& force)
	{
		physic.acc += force;
	}

};
