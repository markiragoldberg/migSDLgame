#include "render.h"

SDL_Texture * text = NULL;
SDL_Renderer *renderer;
SDL_Window *window;
std::unordered_map<std::string, SDL_Texture *> images;

SDL_Texture* loadTexture(const std::string &file)
{
	SDL_Texture *texture = IMG_LoadTexture(renderer, file.c_str());
	if (texture == nullptr){
		logSDLError(std::cout, "LoadTexture");
	}
	return texture;
}

void renderTexture(SDL_Texture *tex, SDL_Rect dst, SDL_Rect *clip)
{
	SDL_RenderCopy(renderer, tex, clip, &dst);
}

void renderTexture(SDL_Texture *tex, int x, int y, SDL_Rect *clip)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	if (clip != nullptr){
		dst.w = clip->w;
		dst.h = clip->h;
	}
	else {
		SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	}
	renderTexture(tex, dst, clip);
}

//this function is bad and only works with one specific image layout
//caveat coder
void renderTextCharacter(char character, int x, int y)
{
	if (text == NULL)
		return;

	SDL_Rect dst;
	dst.w = TEXT_WIDTH;
	dst.h = TEXT_HEIGHT;

	//determine clip
	if (character >= ' ' && character <= '~')
	{
		dst.x = TEXT_WIDTH * ((character - ' ') % 16);
		dst.y = TEXT_HEIGHT *(2 + ((character - ' ') / 16));
	}
	else
	{
		//'?'
		dst.x = TEXT_WIDTH*15; dst.y = TEXT_HEIGHT*3;
	}
	renderTexture(text, x, y, &dst);
}

void logSDLError(std::ostream &os, const std::string &msg)
{
	os << msg << " error: " << SDL_GetError() << std::endl;
}

void loadText(std::string filename)
{
	text = loadTexture(filename);
}

void loadImages(SDL_Renderer *renderer)
{
	images["background"] = loadTexture("png/floor.png");
	images["border"] = loadTexture("png/stone_brick1.png");
	images["orc"] = loadTexture("png/orc.png");
	images["ogre"] = loadTexture("png/two_headed_ogre.png");
	images["worm"] = loadTexture("png/spiny_worm.png");
	images["hound"] = loadTexture("png/hound.png");
	images["orcWarrior"] = loadTexture("png/orc_warrior.png");
	images["orcWizard"] = loadTexture("png/orc_wizard.png");
	images["orcWarlord"] = loadTexture("png/orc_warlord.png");
	images["mace"] = loadTexture("png/mace.png");
	images["greataxe"] = loadTexture("png/greataxe.png");
	images["glaive"] = loadTexture("png/glaive3.png");
	images["handaxe"] = loadTexture("png/hand_axe.png");
	images["club"] = loadTexture("png/club_slant.png");
	images["sword"] = loadTexture("png/long_sword_slant.png");
	images["shield"] = loadTexture("png/shield_kite3.png");
	images["shieldorc"] = loadTexture("png/shield_kite4.png");

	images["fighter"] = loadTexture("png/fighter.png");
	images["barbarian"] = loadTexture("png/barbarian.png");
	images["archer"] = loadTexture("png/archer.png");
	images["rogue"] = loadTexture("png/rogue.png");
	images["cleric"] = loadTexture("png/cleric.png");
	images["wizard"] = loadTexture("png/wizard.png");
	images["textBackground"] = loadTexture("png/volcanic_floor0.png");
	images["UIBorder"] = loadTexture("png/stone_dark0.png");

	images["greatsword"] = loadTexture("png/great_sword_slant.png");
	images["staff"] = loadTexture("png/staff_mage.png");
	images["dagger"] = loadTexture("png/dagger.png");

	images["sword_inv"] = loadTexture("png/long_sword1.png");
	images["shield_inv"] = loadTexture("png/shield1_elven.png");
	images["greatsword_inv"] = loadTexture("png/greatsword2.png");
	images["bow_inv"] = loadTexture("png/longbow.png");
	images["dagger_inv"] = loadTexture("png/dagger_inv.png");
	images["cloak_inv"] = loadTexture("png/cloak2.png");
	images["staff_inv"] = loadTexture("png/staff05.png");
	images["book_inv"] = loadTexture("png/metal_blue.png");
	images["mace_inv"] = loadTexture("png/mace2.png");
}



void printRect(std::string text, int startX, int startY, int w, int h)
{
	//keep track of current width, height offset, char in string
	int maxX = startX + w; int maxY = startY + h;
	int x = startX; int y = startY;
	unsigned i = 0;
	while (i < text.size() && y + TEXT_HEIGHT <= maxY)
	{
		//write char
		renderTextCharacter(text[i], x, y);
		i++;
		x += TEXT_WIDTH;
		if (x + TEXT_WIDTH > maxX)
		{
			x = startX;
			y += TEXT_HEIGHT;
		}
	}
	//while more chars in string and current height plus size of a char less than maximum height
		//figure out what part of the text image the char corresponds to, if any, else use part representing '?'
		//write the char
		//increment char in string, increment current width
		//if current width + width of char > max width, reset current width to 0 and increment current height
}

void deleteRenderingStuff()
{
	if (text != NULL)
		SDL_DestroyTexture(text);
	//clear images
	std::unordered_map<std::string, SDL_Texture*>::iterator i = images.begin();

	for (i = images.begin(); i != images.end();i++)
	
	{
		SDL_DestroyTexture(i->second);
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

int renderingSetup()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		logSDLError(std::cout, "SDL_Init");
		return 1;
	}

	window = SDL_CreateWindow("SDL2", 100, 30, SCREEN_WIDTH,
		SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr){
		logSDLError(std::cout, "CreateWindow");
		SDL_Quit();
		return 1;
	}
	renderer = SDL_CreateRenderer(window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr){
		logSDLError(std::cout, "CreateRenderer");
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	loadText("png/terminal10x16_gs_ro_ts.png");
	loadImages(renderer);
	return 1;
}

void rflush()
{
	SDL_RenderPresent(renderer);
}

void renderDemoSplashScreen()
{
	//Background
	for (int x = TILE_SIZE; x < SCREEN_WIDTH - TILE_SIZE; x += TILE_SIZE)
	{
		for (int y = TILE_SIZE; y < SCREEN_HEIGHT - TILE_SIZE * 8; y += TILE_SIZE)
		{
			renderTexture(images["background"], x, y);
		}
	}
	//Text area background
	for (int x = TILE_SIZE*2; x < SCREEN_WIDTH - TILE_SIZE; x += TILE_SIZE)
	{
		for (int y = SCREEN_HEIGHT - TILE_SIZE * 7; y < SCREEN_HEIGHT - TILE_SIZE; y += TILE_SIZE)
		{
			renderTexture(images["textBackground"], x, y);
		}
	}
	//Bricks along window interior border, border between map and UI elements
	//I think this is too much of a waste of space for a real game,
	//but it looks nice enough for a demo
	for (int x = TILE_SIZE; x < SCREEN_WIDTH - TILE_SIZE; x += TILE_SIZE)
	{
		renderTexture(images["border"], x, 0);
		renderTexture(images["border"], x, SCREEN_HEIGHT - TILE_SIZE);
		//interior map area/text area border
		renderTexture(images["UIBorder"], x, SCREEN_HEIGHT - TILE_SIZE * 8);
	}
	for (int y = 0; y < SCREEN_HEIGHT; y += TILE_SIZE)
	{
		renderTexture(images["border"], 0, y);
		renderTexture(images["border"], SCREEN_WIDTH - TILE_SIZE, y);
	}

	//The party

	renderTexture(images["fighter"], SCREEN_WIDTH / 2 - TILE_SIZE, SCREEN_HEIGHT / 2 - TILE_SIZE);
	renderTexture(images["sword"], SCREEN_WIDTH / 2 - TILE_SIZE, SCREEN_HEIGHT / 2 - TILE_SIZE);
	renderTexture(images["shield"], SCREEN_WIDTH / 2 - TILE_SIZE, SCREEN_HEIGHT / 2 - TILE_SIZE);
	renderTexture(images["archer"], SCREEN_WIDTH / 2 - TILE_SIZE * 5, SCREEN_HEIGHT / 2 - TILE_SIZE * 2);
	renderTexture(images["barbarian"], SCREEN_WIDTH / 2 - TILE_SIZE * 2, SCREEN_HEIGHT / 2 - TILE_SIZE);
	renderTexture(images["greatsword"], SCREEN_WIDTH / 2 - TILE_SIZE * 2, SCREEN_HEIGHT / 2 - TILE_SIZE);
	renderTexture(images["wizard"], SCREEN_WIDTH / 2 - TILE_SIZE * 2, SCREEN_HEIGHT / 2);
	renderTexture(images["staff"], SCREEN_WIDTH / 2 - TILE_SIZE * 2, SCREEN_HEIGHT / 2);
	renderTexture(images["cleric"], SCREEN_WIDTH / 2 - TILE_SIZE * 3, SCREEN_HEIGHT / 2 + TILE_SIZE);
	renderTexture(images["mace"], SCREEN_WIDTH / 2 - TILE_SIZE * 3, SCREEN_HEIGHT / 2 + TILE_SIZE);
	renderTexture(images["rogue"], SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	renderTexture(images["dagger"], SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	//The orcs and their allies

	renderTexture(images["orcWarlord"], SCREEN_WIDTH / 2 + TILE_SIZE, SCREEN_HEIGHT / 2 - TILE_SIZE * 2);
	renderTexture(images["glaive"], SCREEN_WIDTH / 2 + TILE_SIZE, SCREEN_HEIGHT / 2 - TILE_SIZE * 2);

	renderTexture(images["orcWarrior"], SCREEN_WIDTH / 2 + TILE_SIZE * 2, SCREEN_HEIGHT / 2 - TILE_SIZE * 3);
	renderTexture(images["sword"], SCREEN_WIDTH / 2 + TILE_SIZE * 2, SCREEN_HEIGHT / 2 - TILE_SIZE * 3);
	renderTexture(images["shieldorc"], SCREEN_WIDTH / 2 + TILE_SIZE * 2, SCREEN_HEIGHT / 2 - TILE_SIZE * 3);
	renderTexture(images["orcWarrior"], SCREEN_WIDTH / 2 + TILE_SIZE, SCREEN_HEIGHT / 2 - TILE_SIZE * 3);
	renderTexture(images["greataxe"], SCREEN_WIDTH / 2 + TILE_SIZE,SCREEN_HEIGHT / 2 - TILE_SIZE * 3);

	renderTexture(images["orcWizard"], SCREEN_WIDTH / 2 + TILE_SIZE * 2, SCREEN_HEIGHT / 2 - TILE_SIZE * 5);

	renderTexture(images["orc"], SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - TILE_SIZE * 3);
	renderTexture(images["mace"], SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - TILE_SIZE * 3);

	renderTexture(images["ogre"], SCREEN_WIDTH / 2 - TILE_SIZE * 3, SCREEN_HEIGHT / 2 - TILE_SIZE * 3);

	renderTexture(images["worm"], SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - TILE_SIZE * 5);

	renderTexture(images["orc"], SCREEN_WIDTH / 2 - TILE_SIZE, SCREEN_HEIGHT / 2 - TILE_SIZE * 4);
	renderTexture(images["handaxe"], SCREEN_WIDTH / 2 - TILE_SIZE, SCREEN_HEIGHT / 2 - TILE_SIZE * 4);

	renderTexture(images["orc"], SCREEN_WIDTH / 2 - TILE_SIZE, SCREEN_HEIGHT / 2 - TILE_SIZE * 6);
	renderTexture(images["club"], SCREEN_WIDTH / 2 - TILE_SIZE, SCREEN_HEIGHT / 2 - TILE_SIZE * 6);

	//Giant hideous poorly-scaled portrait of orc warlord on the left
	SDL_Rect portrait;
	portrait.x = TILE_SIZE; portrait.y = TILE_SIZE;
	portrait.w = TILE_SIZE * 8; portrait.h = TILE_SIZE * 11;
	renderTexture(images["orcWarlord"], portrait);
	renderTexture(images["glaive"], portrait);

	printRect("Fred,", TILE_SIZE * 4, TILE_SIZE * 7, (TILE_SIZE * 15)/2, TEXT_HEIGHT);
	printRect("the Orc Warlord", (TILE_SIZE * 3)/2, (TILE_SIZE * 15)/2, (TILE_SIZE * 15)/2, TEXT_HEIGHT);

	//Encounter options on the right
	printRect("Your party runs into a few orcs. What do you do?", TILE_SIZE * 18, TILE_SIZE * 2, SCREEN_WIDTH - TILE_SIZE * 19,TILE_SIZE*2);

	printRect("1 - Try to negotiate.", TILE_SIZE * 18, TILE_SIZE * 4, SCREEN_WIDTH - TILE_SIZE * 19, TILE_SIZE * 2);
	printRect("2 - Fight the orcs!", TILE_SIZE * 18, TILE_SIZE * 5, SCREEN_WIDTH - TILE_SIZE * 19, TILE_SIZE * 2);
	printRect("3 - Run away!", TILE_SIZE * 18, TILE_SIZE * 6, SCREEN_WIDTH - TILE_SIZE * 19, TILE_SIZE * 2);
	printRect("4 - Surrender.", TILE_SIZE * 18, TILE_SIZE * 7, SCREEN_WIDTH - TILE_SIZE * 19, TILE_SIZE * 2);

	//Party info area

	//TERENCE, THE FIGHTER
	printRect(" Terence, the Fighter",
		TILE_SIZE * 2, SCREEN_HEIGHT - TEXT_HEIGHT * 14, SCREEN_WIDTH - TILE_SIZE*6, TEXT_HEIGHT);
	printRect(" HP:  20/20  MP   2/3   Confident",
		TILE_SIZE * 2, SCREEN_HEIGHT - TEXT_HEIGHT * 13, SCREEN_WIDTH - TILE_SIZE * 6, TEXT_HEIGHT);
	renderTexture(images["fighter"], TILE_SIZE, SCREEN_HEIGHT - TILE_SIZE * 7);
	renderTexture(images["sword"], TILE_SIZE, SCREEN_HEIGHT - TILE_SIZE * 7);
	renderTexture(images["shield"], TILE_SIZE, SCREEN_HEIGHT - TILE_SIZE * 7);
	renderTexture(images["sword_inv"], SCREEN_WIDTH-TILE_SIZE*4, SCREEN_HEIGHT - TILE_SIZE * 7);
	renderTexture(images["shield_inv"], SCREEN_WIDTH - TILE_SIZE * 3, SCREEN_HEIGHT - TILE_SIZE * 7);
	//NORRIS, THE BARBARIAN
	printRect(" Norris, the Barbarian",
		TILE_SIZE * 2, SCREEN_HEIGHT - TILE_SIZE * 6, SCREEN_WIDTH - TILE_SIZE * 6, TEXT_HEIGHT);
	printRect(" HP:  34/34  MP   0/0   Unshakeable",
		TILE_SIZE * 2, SCREEN_HEIGHT - TEXT_HEIGHT * 11, SCREEN_WIDTH - TILE_SIZE * 6, TEXT_HEIGHT);
	renderTexture(images["barbarian"], TILE_SIZE, SCREEN_HEIGHT - TILE_SIZE * 6);
	renderTexture(images["greatsword"], TILE_SIZE, SCREEN_HEIGHT - TILE_SIZE * 6);
	renderTexture(images["greatsword_inv"], SCREEN_WIDTH - TILE_SIZE * 4, SCREEN_HEIGHT - TILE_SIZE * 6);
	//NESSUS, THE ARCHER
	printRect(" Nessus, the Archer",
		TILE_SIZE * 2, SCREEN_HEIGHT - TILE_SIZE * 5, SCREEN_WIDTH - TILE_SIZE * 6, TEXT_HEIGHT);
	printRect(" HP:  18/18  MP   1/1   Steady",
		TILE_SIZE * 2, SCREEN_HEIGHT - TEXT_HEIGHT * 9, SCREEN_WIDTH - TILE_SIZE * 6, TEXT_HEIGHT);
	renderTexture(images["archer"], TILE_SIZE, SCREEN_HEIGHT - TILE_SIZE * 5);
	renderTexture(images["bow_inv"], SCREEN_WIDTH - TILE_SIZE * 4, SCREEN_HEIGHT - TILE_SIZE * 5);
	//MAURICE, THE ROGUE
	printRect(" Maurice, the Rogue",
		TILE_SIZE * 2, SCREEN_HEIGHT - TILE_SIZE * 4, SCREEN_WIDTH - TILE_SIZE * 6, TEXT_HEIGHT);
	printRect(" HP:  14/14  MP   6/11  Self-certain",
		TILE_SIZE * 2, SCREEN_HEIGHT - TEXT_HEIGHT * 7, SCREEN_WIDTH - TILE_SIZE * 6, TEXT_HEIGHT);
	renderTexture(images["rogue"], TILE_SIZE, SCREEN_HEIGHT - TILE_SIZE * 4);
	renderTexture(images["dagger"], TILE_SIZE, SCREEN_HEIGHT - TILE_SIZE * 4);
	renderTexture(images["dagger_inv"], SCREEN_WIDTH - TILE_SIZE * 4, SCREEN_HEIGHT - TILE_SIZE * 4);
	renderTexture(images["cloak_inv"], SCREEN_WIDTH - TILE_SIZE * 3, SCREEN_HEIGHT - TILE_SIZE * 4);
	//MENNAS, THE CLERIC
	printRect(" Mennas, the Cleric",
		TILE_SIZE * 2, SCREEN_HEIGHT - TILE_SIZE * 3, SCREEN_WIDTH - TILE_SIZE * 6, TEXT_HEIGHT);
	printRect(" HP:  17/17  MP  14/18  Zealous",
		TILE_SIZE * 2, SCREEN_HEIGHT - TEXT_HEIGHT * 5, SCREEN_WIDTH - TILE_SIZE * 6, TEXT_HEIGHT);
	renderTexture(images["cleric"], TILE_SIZE, SCREEN_HEIGHT - TILE_SIZE * 3);
	renderTexture(images["mace"], TILE_SIZE, SCREEN_HEIGHT - TILE_SIZE * 3);
	renderTexture(images["mace_inv"], SCREEN_WIDTH - TILE_SIZE * 4, SCREEN_HEIGHT - TILE_SIZE * 3);
	renderTexture(images["book_inv"], SCREEN_WIDTH - TILE_SIZE * 3, SCREEN_HEIGHT - TILE_SIZE * 3);
	//BORIS, THE WIZARD
	printRect(" Boris, the Wizard",
		TILE_SIZE * 2, SCREEN_HEIGHT - TILE_SIZE * 2, SCREEN_WIDTH - TILE_SIZE * 6, TEXT_HEIGHT);
	printRect(" HP:   9/9   MP  24/29  Focused",
		TILE_SIZE * 2, SCREEN_HEIGHT - TEXT_HEIGHT*3, SCREEN_WIDTH - TILE_SIZE * 6, TEXT_HEIGHT);
	renderTexture(images["wizard"], TILE_SIZE, SCREEN_HEIGHT - TILE_SIZE * 2);
	renderTexture(images["staff"], TILE_SIZE, SCREEN_HEIGHT - TILE_SIZE * 2);
	renderTexture(images["staff_inv"], SCREEN_WIDTH - TILE_SIZE * 4, SCREEN_HEIGHT - TILE_SIZE * 2);

	

	SDL_RenderPresent(renderer);
}

void clearDemoMapArea()
{
	//Background
	for (int x = TILE_SIZE; x < SCREEN_WIDTH - TILE_SIZE; x += TILE_SIZE)
	{
		for (int y = TILE_SIZE; y < SCREEN_HEIGHT - TILE_SIZE * 8; y += TILE_SIZE)
		{
			renderTexture(images["background"], x, y);
		}
	}
	rflush();
}
