#include <iostream>
#include <SDL.h>
#include "render.h"
#include "encounters.h"
#include "demo.h"
#undef main

int main()
{
	if (!loadData() || !renderingSetup())
	{
		return 1;
	}
	demoLoop();
	deleteRenderingStuff();
	SDL_Quit();
	deleteEncounters();
	return 0;
}
