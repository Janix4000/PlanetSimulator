#pragma once

#include "FollowingBehavior.h"

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
	}

	void setTarget(const Planet& target)
	{
		behavior.setTarget(target);
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
		setPosition(getPosition() + shift);
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