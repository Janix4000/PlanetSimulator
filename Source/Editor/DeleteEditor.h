#pragma once

#include "BaseEditor.h"

class DeleteEditor
	:
	public BaseEditor
{
public:
	DeleteEditor(PlanetHolder& holder)
		:
		BaseEditor(Key::BackSpace, holder)
	{
	}

private:

	void init() override
	{
		getPlanet().kill();
	}
};