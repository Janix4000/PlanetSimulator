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

	float getNewRadiusByMass(float newMass) const;

	float getNewMassByRadius(float newRadius) const;

	sf::Color getRandomColor(int spacing = 16) const;

	char getRandomColorParameter(Random<>& rng, int spacing = 1) const;


	Vec2 getForceVecBetween(const Planet& other);

	Vec2 getDistVecBetween(const Planet& other);

	void applyForce(const Vec2& force);

};
