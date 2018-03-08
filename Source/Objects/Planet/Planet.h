#pragma once

#include "../FreePhysics.h"

#include "../../Utilities/Vec2.h"
#include "../../Utilities/Random.h"

#define G 100.f

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
	auto getPosition()const { return physic.pos; }
	void setVelocity(const Vec2& newVelocity);
	auto getVelocity() const { return physic.vel; }
	auto getAcc() const { return physic.oldAcc; }

	void kill() { alive = false; }
	bool isAlive() const { return alive; }

	void consume(Planet& meal)
	{
		if (meal.isAlive())
		{
			const float totalMass = mass + meal.mass;

			auto newPos = (meal.getPosition() * meal.mass + getPosition() * mass) / totalMass;
			auto newVel = (meal.getVelocity() * meal.mass + getVelocity() * mass) / totalMass;
			auto newColor = getMixedColor(circle.getFillColor(), meal.circle.getFillColor(), mass / totalMass);

			setMass(totalMass);
			setVelocity(newVel);
			setPosition(newPos);

			meal.setMass(0.f);	
			meal.kill();
		}
	}

	bool isOverlappingEnoughToMerge(const Planet& other, float tolerance = 0.75f) const
	{
		auto distVec = getDistVecBetween(other);
		float distSqr = distVec.getLenSq();
		float radiusSumSqr = pow(getRadius() + other.getRadius(), 2);
		float tolSqr = pow(tolerance, 2);

		return distSqr <= tolSqr * radiusSumSqr;
	}

	bool isOverlappingPoint(const Vec2& point) const
	{
		const auto distVec = getPosition() - point;
		const float distSqr = distVec.getLenSq();

		return distSqr <= pow(getRadius(), 2);
	}

private:
	FreePhysics physic;

	float mass;
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

	Vec2 getDistVecBetween(const Planet& other) const;

	void applyForce(const Vec2& force);

	sf::Color getMixedColor(sf::Color first,sf::Color second, float firstColorRatio = 0.5f)
	{
		int fRatio = int(255.f * firstColorRatio);
		int sRatio = 255 - fRatio;


		int fR = int(first.r), fG = int(first.g), fB = int(first.b);
		int sR = int(second.r), sG = int(second.g), sB = int(second.b);

		int newR = (fRatio * fR + sRatio * sR) / 256;
		int newG = (fRatio * fG + sRatio * sG) / 256;
		int newB = (fRatio * fB + sRatio * sB) / 256;

		return sf::Color(newR, newG, newB);
	}

	void renderVecs(sf::RenderTarget& renderer) const
	{
		auto velLine = getLineInReferenceToPos(getVelocity(), sf::Color::Blue);
		auto accLine = getLineInReferenceToPos(getAcc(), sf::Color::Red);

		renderer.draw(velLine);
		renderer.draw(accLine);
	}

	sf::VertexArray getLineInReferenceToPos(Vec2 line, sf::Color c) const
	{
		sf::VertexArray lines(sf::LinesStrip, 2);
		lines[0].position = getPosition();
		lines[1].position = getPosition() + line;
		lines[0].color = c;
		lines[1].color = c;

		return lines;
	}

};
