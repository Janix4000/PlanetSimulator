#pragma once
#include <SFML/Graphics.hpp>

#include "../Objects/Planet.h"

class Orbit
{
public:
	Orbit()
	{
		ellipse.setFillColor(sf::Color::Transparent);
		ellipse.setOutlineColor(sf::Color::White);
		ellipse.setOutlineThickness(2.f);
	}

	void render(sf::RenderTarget& renderer) const
	{
		renderer.draw(ellipse);
	}

	void setOrbiter(Planet& newOrbiter) { orbiter = &newOrbiter; }
	void setSun(Planet& newSun) { sun = &newSun; }

	void setOrbiterPos(const Vec2& newPosition)
	{

		orbiter->setPosition(newPosition);
		calcEllipse();
		calcOrbiterVelocity();
	}

	void free()
	{
		orbiter = nullptr;
		sun = nullptr;
	}

	void addToEFactor(float addon)
	{
		e += addon;
		if (e < 0.f) e = 0.f;
		if (e > 0.6) e = 0.6;
	}

private:

	sf::CircleShape ellipse;

	float e{0.7f};

	Planet* sun{ nullptr };
	Planet* orbiter{ nullptr };

	float rPer, rAp, r, widthFactor, theta;

	void calcEllipse()
	{
		calcPeryhelium();
		calcTheta();

		calcAphelium();
		calcRadius();

		calcWidthFactor();
		
		transformEllipse();
	}

	void calcPeryhelium()
	{
		const auto distVec =  sun->getPosition() - orbiter->getPosition();
		const float dist = distVec.getLen();
		rPer = dist;
	}

	void calcAphelium()
	{
		rAp = rPer * (1.f + e) / (1.f - e);
	}

	void calcRadius()
	{
		r = sqrt(rAp * rPer);
	}

	void calcWidthFactor()
	{
		const float width = rPer + rAp;
		widthFactor = (width / (2.f*r));
	}

	void calcTheta()
	{
		const auto distVec = sun->getPosition() - orbiter->getPosition();
		theta = distVec.getAngleBetweenInDegrees({ 0.f, 1.f });

		//std::cout << "Degree: " << theta << "\n";
	}

	void transformEllipse()
	{
		ellipse.setRadius(r);
		ellipse.setOrigin(r, r);
		ellipse.setScale(widthFactor, 1.f);

		const float originX = rPer / widthFactor;
		ellipse.setOrigin(originX, r);
		ellipse.setRotation(theta);

		ellipse.setPosition(sun->getPosition());
	}

	void calcOrbiterVelocity()
	{		
		const auto newVelocity = getNewVelocity();		
		orbiter->setVelocity(newVelocity);
	}

	float getSpeed() const
	{
		float a = (rAp + rPer) / 2.f;
		return sqrt(((1.f + e)*sun->getMass()*G) / ((1.f - e)*a));
	}

	Vec2 getNewVelocity()
	{
		const auto distVec = sun->getPosition() - orbiter->getPosition();
		float speed = getSpeed();
		auto newVelocity = distVec.getPerpendicular();
		newVelocity.setLen(speed);
		return newVelocity;
	}
};