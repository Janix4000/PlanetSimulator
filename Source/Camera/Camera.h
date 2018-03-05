#pragma once

#include "FollowingBehavior.h"

class Camera
{
public:

	Camera()
	{
		cam.setSize(1280.f, 720.f);
		physic.pos = { 0.f, 0.f };
	}

	void update(float dt)
	{
		updatePhysic(dt);
	}

	void setPosition(const sf::Vector2f& position)
	{
		behavior.setTarget(position);
	}

	sf::Vector2f getPosition() const
	{
		return cam.getCenter();
	}

	void free()
	{
		behavior.stop(physic);
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
		behavior.applyTo(dt, physic);
		physic.update(dt);
		applyPhysikToView();

	}

	void applyPhysikToView()
	{
		cam.setCenter(physic.pos);
	}
};