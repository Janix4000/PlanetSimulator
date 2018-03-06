#include "PlanetManager.h"

PlanetManager::PlanetManager(Camera & mainCamera)
	:
	mainCamera(&mainCamera)
{
	run.setFillColor(sf::Color::Green);
	pause.setFillColor(sf::Color::Yellow);
	edit.setFillColor(sf::Color::Red);

	const Vec2 dimension = { 32.f, 32.f };

	run.setSize(dimension);
	pause.setSize(dimension);
	edit.setSize(dimension);

	run.setPosition(0.f, 0.f);
	pause.setPosition(0.f, 0.f);
	edit.setPosition(0.f, 0.f);
}

void PlanetManager::update(float dt)
{
	refresh();

	switch (state)
	{
	case State::Running:
		updateAllPlanets(dt);
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
		state = State::Pause;
	}
}

void PlanetManager::updateAllPlanets(float dt)
{
	attractAllPlanets();
	for (auto& planet : planets)
	{
		planet->update(dt);
	}
	handlePlanetCrushing();
	refresh();
}

void PlanetManager::attractAllPlanets()
{
	for (int i = 0; i < planets.size(); i++)
	{
		auto& planet = planets[i];
		for (int j = i + 1; j < planets.size(); j++)
		{
			auto& nextPlanet = planets[j];
			planet->attractBoth(*nextPlanet);
		}
	}
}

void PlanetManager::handlePlanetCrushing()
{
	for (int i = 0; i < planets.size(); i++)
	{
		auto& planet = planets[i];
		for (int j = i + 1; j < planets.size(); j++)
		{
			auto& nextPlanet = planets[j];
			if (nextPlanet->isOverlappingEnoughToMerge(*planet))
			{
				if (isSelected(*planet)) selectPlanet(*nextPlanet);
				nextPlanet->consume(*planet);
				break;
			}
		}
	}
}

void PlanetManager::refresh()
{
	planets.erase(std::remove_if(planets.begin(), planets.end(), [](const auto& planet) {
		return !planet->isAlive();
	}), planets.end());
}


void PlanetManager::render(sf::RenderTarget & renderer) const
{
	for (const auto& planet : planets)
	{
		planet->render(renderer);
	}

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
	if (e.type == sf::Event::KeyPressed)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			state = State::Pause;
		}
	}
	handlePlanetSelecting(e, window);
}

void PlanetManager::handleEditingEvent(sf::Event e, const sf::RenderWindow & window)
{
	editor.handleEvent(e, window);
	if (!editor.isEditing())
	{
		state = State::Pause;
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
	if (handlePlanetSelecting(e, window))
	{
		startEditingSelectedPlanet();
		unSelect();
	}
}



Planet * PlanetManager::addPlanet()
{
	auto planet = std::make_unique<Planet>();
	auto planetPtr = planet.get();

	planets.emplace_back(std::move(planet));
	return planetPtr;
}


void PlanetManager::startEditing(Planet & planet)
{
	state = State::Editing;
	editor.edit(planet);
}

void PlanetManager::startEditingSelectedPlanet()
{
	auto planet = getSelectedPlanetPtr();

	if (planet != nullptr) startEditing(*planet);
}

void PlanetManager::selectPlanet(Planet & planet)
{
	selectedPlanet = &planet;
	mainCamera->setTarget(planet);
}

bool PlanetManager::isSelected(const Planet & planet) const { return selectedPlanet == &planet; }

Planet * PlanetManager::getSelectedPlanetPtr() { return selectedPlanet; }

void PlanetManager::unSelect()
{
	selectedPlanet = nullptr;
	mainCamera->free();
}

bool PlanetManager::handlePlanetSelecting(sf::Event e, const sf::RenderWindow & window)
{
	if (e.type == sf::Event::MouseButtonPressed)
	{
		auto clicked = getOverlappingCursorPlanetPtr(window);
		if (clicked != nullptr)
		{
			selectPlanet(*clicked);
			return true;
		}
	}
	return false;
}

Planet * PlanetManager::getOverlappingCursorPlanetPtr(const sf::RenderWindow & window)
{
	const auto mousePos = getRealMousePos(window);

	auto overlapper = std::find_if(planets.begin(), planets.end(), [&](std::unique_ptr<Planet>& planet) {
		return planet->isOverlappingPoint(mousePos);
	});

	if (overlapper == planets.end()) return nullptr;

	return overlapper->get();
}

void PlanetManager::handleAddingEvent(sf::Event e, const sf::RenderWindow & window)
{
	switch (e.type)
	{
	case sf::Event::KeyPressed:
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		{
			auto& newPlanet = *addPlanet();

			auto mousePos = getRealMousePos(window);
			newPlanet.setPosition(mousePos);
		}
		break;
	}
}


