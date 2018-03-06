#pragma once
#include "../Objects/Planet.h"

#include "BaseEditor.h"

#include "VelocityEditor.h"
#include "PositionEditor.h"
#include "RadiusEditor.h"

#include <vector>
#include <memory>
#include <algorithm>

class PlanetEditor
{
public:

	PlanetEditor()
	{
		editors.emplace_back(std::make_unique<VelocityEditor>());
		editors.emplace_back(std::make_unique<PositionEditor>());
		editors.emplace_back(std::make_unique<RadiusEditor>());
	}

	void update(float dt) 
	{
		if (isEditing())
		{
			for (auto& editor : editors)
			{
				editor->update(dt);
			}
		}
	}

	void render(sf::RenderTarget& renderer) const 
	{
		if (isEditing())
		{
			for (auto& editor : editors)
			{
				editor->render(renderer);
			}
		}	
	}

	void handleInput(const sf::RenderWindow& window)
	{
		if (isEditing())
		{
			for (auto& editor : editors)
			{
				editor->handleInput(window);
			}
		}
	}

	void handleEvent(sf::Event e, const sf::RenderWindow& window)
	{
		if (isEditing())
		{
			auto activeOne = std::find_if(editors.begin(), editors.end(), [](auto& editor) {
				return editor->isActive();
			});

			if (activeOne == editors.end())
			{
				if (e.type == sf::Event::MouseButtonPressed)
				{
					if (isEditing())
					{
						end();
					}
				}

				for (auto& editor : editors)
				{
					editor->handleEvent(e, window);
				}
			}
			else
			{
				(*activeOne)->handleEvent(e, window);
			}

		
			if (e.type == sf::Event::KeyPressed)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
				{
					end();
				}
			}
		}
	}

	void edit(Planet& planet)
	{
		editingPlanet = &planet;
		editing = true;
		for (auto& editor : editors)
		{
			editor->setNewTarget(planet);
		}
	}

	void end()
	{
		for (auto& editor : editors)
		{
			editor->freePlanet();
		}
		editing = false;
	}

	bool isEditing() const
	{
		return editing;
	}

private:

	Planet * editingPlanet = {nullptr};

	std::vector<std::unique_ptr<BaseEditor>> editors;

	bool editing{ false };
};