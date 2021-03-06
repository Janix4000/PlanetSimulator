#include "PlanetManager.h"

#include <iostream>

PlanetManager::PlanetManager(Camera& cam)
	:
	mainCamera(&cam),
	editor(holder)
{
	run.setFillColor(sf::Color::Green);
	pause.setFillColor(sf::Color::Yellow);
	edit.setFillColor(sf::Color::Red);

	const float dimension = 16.f;

	run.setRadius(dimension);
	pause.setRadius(dimension);
	edit.setRadius(dimension);

	run.setPosition(0.f, 0.f);
	pause.setPosition(0.f, 0.f);
	edit.setPosition(0.f, 0.f);
}

void PlanetManager::update(float dt)
{
	switch (state)
	{
	case State::Running:
		updatePlanets(dt);
		break;

	case State::Editing:
		updateEditor(dt);
		break;

	default:
		break;
	}
}

void PlanetManager::updateEditor(float dt)
{
	editor.update(dt);
	if (!editor.isEditing())
	{
		std::cout << "End of editing\n";
		changeStateToPause();
	}
}


void PlanetManager::updatePlanets(float dt)
{
	holder.update(dt);
}

void PlanetManager::render(sf::RenderTarget & renderer) const
{
	holder.render(renderer);
	editor.render(renderer);

	renderIcons(renderer);
}

void PlanetManager::renderIcons(sf::RenderTarget & renderer) const
{
	auto oldView = renderer.getView();
	sf::View iconsView;
	iconsView.setSize(sf::Vector2f(renderer.getSize()));
	iconsView.setCenter(sf::Vector2f(renderer.getSize() / 2u));

	renderer.setView(iconsView);

	switch (state)
	{
	case State::Running:
		renderer.draw(run);
		break;

	case State::Editing:
		renderer.draw(edit);

		break;

	case State::Pause:
		renderer.draw(pause);

		break;

	default:
		break;
	}

	renderer.setView(oldView);
}

void PlanetManager::handleEvent(sf::Event e, const sf::RenderWindow & window)
{
	switch (state)
	{
	case State::Running:
		handleRunningEvent(e, window);
		break;

	case State::Editing:
		handleEditingEvent(e, window);
		break;

	case State::Pause:
		handlePauseEvent(e, window);
		break;

	default:
		break;
	}
}

void PlanetManager::handleRunningEvent(sf::Event e, const sf::RenderWindow & window)
{
	holder.handleEvent(e, window);

	if (holder.isClicked() || holder.isReadyToCamFollow())
	{
		mainCamera->setTarget(holder.getSelectedPlanet());
		holder.removeReadyToCamMark();
	}

	if (e.type == sf::Event::KeyPressed)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			changeStateToPause();
			mainCamera->free();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			holder.selectNextPlanet();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			holder.selectPreviousPlanet();
		}
	}
}


void PlanetManager::handleEditingEvent(sf::Event e, const sf::RenderWindow & window)
{
	editor.handleEvent(e, window);
	handleDeleteEvent(e, window);


	if (!editor.isEditing())
	{
		changeStateToPause();
	}
}

void PlanetManager::handlePauseEvent(sf::Event e, const sf::RenderWindow & window)
{
	handleAddingEvent(e, window);
	if (e.type == sf::Event::KeyPressed)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			state = State::Running;
		}
	}

	holder.handleEvent(e, window);
	startEditingClickedPlanet();
}

void PlanetManager::handleInput(const sf::RenderWindow & window)
{
	switch (state)
	{
	case State::Running:
		break;

	case State::Editing:
		editor.handleInput(window);
		break;

	case State::Pause:
		break;

	default:
		break;
	}
}

void PlanetManager::startEditing(Planet & planet)
{
	state = State::Editing;
	editor.edit(planet);
	mainCamera->goTo(planet);
}

void PlanetManager::startEditingClickedPlanet()
{
	if (holder.isClicked())
	{
		startEditing(holder.getSelectedPlanet());
		std::cout << "Editing started\n";
	}
}

void PlanetManager::handleAddingEvent(sf::Event e, const sf::RenderWindow & window)
{
	switch (e.type)
	{
	case sf::Event::KeyPressed:
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		{
			auto& newPlanet = *holder.addPlanet();

			auto mousePos = getRealMousePos(window);
			newPlanet.setPosition(mousePos);
			startEditing(newPlanet);
		}
		break;
	}
}

void PlanetManager::handleDeleteEvent(sf::Event e, const sf::RenderWindow & window)
{
	switch (e.type)
	{
	case sf::Event::KeyPressed:
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
		{
			if (editor.isEditing())
			{
				deleteEdited();
				changeStateToPause();
			}
		}
		break;
	}
}

void PlanetManager::deleteEdited()
{
	auto& planet = holder.getSelectedPlanet();

	if (&(holder.getSelectedPlanet()) == (editor.getEditedPlanetPtr()))
	{
		std::cout << "Alright deleting\n";
	}
	else
	{
		std::cout << "Something is wrong\n";
	}

	editor.end();
	planet.kill();
	holder.refresh();

	if (holder.isSelectedRemoved())
	{
		std::cout << "Camera is free now\n";
		mainCamera->free();
	}
}

void PlanetManager::changeStateToPause()
{
	state = State::Pause;
	mainCamera->free();
}
