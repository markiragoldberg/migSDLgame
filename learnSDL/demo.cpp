#include "demo.h"

int demoLoop()
{
	renderDemoSplashScreen();

	initRandomization();

	bool quit = false;
	unsigned e = 0;
	do
	{
		const encounter * enc = getEncounter(e);
		const dialogueNode * diag = enc->dialogue("start");
		bool nextEncounter = false;
		e++;
		do
		{
			clearDemoMapArea();
			printRect(diag->text(), TILE_SIZE, TILE_SIZE, SCREEN_WIDTH - TILE_SIZE * 2, TILE_SIZE * 8);
			int i = 0;
			while (diag->option(i) != "")
			{
				std::stringstream option;
				option << i + 1 << " - " << enc->dialogue(diag->option(i))->trans();
				printRect(option.str().c_str(), TILE_SIZE, TILE_SIZE * (i + 5), SCREEN_WIDTH - TILE_SIZE * 2, TILE_SIZE * 8 - i * TILE_SIZE);
				i++;
			}
			if (diag->id() == "wonCombat")
			{
				std::stringstream monList;
				monList << "You defeated ";
				unsigned m = 0;
				while (enc->monsterCount(m) != 0)
				{
					monList << enc->monsterCount(m) << " " << enc->monsterType(m) << "s";
					if (enc->monsterCount(m+2) == 0 && enc->monsterCount(m+1) != 0)
					{
						monList << ", and ";
					}
					else if (enc->monsterCount(m + 1) == 0)
					{
						monList << ". ";
					}
					else
					{
						monList << ", ";
					}
					m++;
				}
				monList << "You found " << naive_d6() << ", " << naive_d6() << ", " << naive_d6() << ", " << naive_d6() << ", " << naive_d6() << ", " << naive_d6() << ", " << naive_d6() << ", " << naive_d6() << ", " << naive_d6() << ", " << naive_d6() << ", " << naive_d6() << ", " << " copper pieces.";
				printRect(monList.str().c_str(), TILE_SIZE, TILE_SIZE * (i + 5), SCREEN_WIDTH - TILE_SIZE * 2, TILE_SIZE * 8 - i * TILE_SIZE);
			}
			rflush();

			std::string opt = "";
			do
			{
				SDL_Event input;
				if (SDL_PollEvent(&input))
				{
					if (input.type == SDL_KEYDOWN && input.key.keysym.sym >= SDLK_1 && input.key.keysym.sym <= SDLK_9)
					{
						opt = diag->option(input.key.keysym.sym - SDLK_1);
					}
					if ((input.key.repeat == 0 && input.type == SDL_KEYDOWN && input.key.keysym.sym == SDLK_ESCAPE) ||
						input.type == SDL_QUIT)
					{
						quit = true;
					}
					if (diag->ending() && input.type == SDL_KEYDOWN)
					{
						if (diag->combat() && enc->dialogue("wonCombat") != NULL)
							opt = "wonCombat";
						else
							nextEncounter = true;
					}
				}
			} while (!quit && !nextEncounter && opt == "");
			if (opt != "")
			{
				diag = enc->dialogue(opt);
			}
		} while (!quit && !nextEncounter);
	} while (!quit && getEncounter(e) != NULL);

	return 0;
}
