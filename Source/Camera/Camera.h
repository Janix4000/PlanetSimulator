#pragma once

#include "FollowingBehavior.h"

#include <iostream>

class Camera
{
public:

	Camera()
		:
		behavior(physic)
	{
		cam.setSize(1280.f, 720.f);
		physic.pos = { 0.f, 0.f };
	}

	void update(float dt)
	{
		updatePhysic(dt);

		//std::cout << "Cam pos: x:" << getPosition().x << " y:" << getPosition().y << "\n";

	}

	void setTarget(const Planet& target)
	{
		behavior.setTarget(target);
	}

	void goTo(const Planet& target)
	{
		behavior.goTo(target);
	}

	sf::Vector2f getPosition() const
	{
		return cam.getCenter();
	}

	void setPosition(const sf::Vector2f newPosition)
	{
		free();
		physic.pos = { newPosition.x, newPosition.y };
		applyPhysikToView();
	}

	void move(sf::Vector2f shift)
	{
		shift *= totalFactor;

		setPosition(getPosition() + shift);
	}

	void zoom(float addon)
	{
		float factor = 1.f + addon;

		float newTotalFactor = totalFactor * factor;

		if (newTotalFactor > 5.f || newTotalFactor < 0.1f) return;
		else
		{
			totalFactor = newTotalFactor;
			cam.zoom(factor);
		}
	}

	void free()
	{
		behavior.changeStateToFree();
	}

	void applyToWindow(sf::RenderTarget& window) const
	{
		window.setView(cam);
	}

	sf::Vector2f getMousePosition(const sf::RenderWindow& window) const
	{
		sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
		return window.mapPixelToCoords(pixelPos);
	}

private:

	sf::View cam;

	float totalFactor{ 1.f };

	FollowingBehavior behavior;
	FreePhysics physic;

	void updatePhysic(float dt)
	{
		behavior.update(dt);
		physic.update(dt);
		applyPhysikToView();
	}

	void applyPhysikToView()
	{
		cam.setCenter(physic.pos);
	}
};