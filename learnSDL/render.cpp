#include "render.h"

SDL_Texture * text = NULL;
std::unordered_map<std::string, SDL_Texture *> images;

SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren)
{
	SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
	if (texture == nullptr){
		logSDLError(std::cout, "LoadTexture");
	}
	return texture;
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, SDL_Rect dst, SDL_Rect *clip)
{
	SDL_RenderCopy(ren, tex, clip, &dst);
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, SDL_Rect *clip)
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
	renderTexture(tex, ren, dst, clip);
}


void renderTextCharacter(char character, SDL_Renderer *ren, int x, int y)
{
	if (text == NULL)
		return;

	SDL_Rect dst;
	dst.w = dst.h = TEXT_SIZE;

	//determine clip
	if (character >= 'A' && character <= 'Z')
	{
		dst.x = TEXT_SIZE * (character-'A');
		dst.y = TEXT_SIZE * 3;
	}
	else if (character >= 'a' && character <= 'z')
	{
		dst.x = TEXT_SIZE * (character-'a');
		dst.y = TEXT_SIZE * 4;
	}
	else if (character >= ' ' && character <= '@')
	{
		dst.x = TEXT_SIZE * ((character - ' ') % 32);
		dst.y = TEXT_SIZE * ((character - ' ') / 32);
	}
	else
	{
		//'?'
		dst.x = TEXT_SIZE*31; dst.y = 0;
	}
	renderTexture(text, ren, x, y, &dst);
}

void logSDLError(std::ostream &os, const std::string &msg)
{
	os << msg << " error: " << SDL_GetError() << std::endl;
}

void loadText(std::string filename, SDL_Renderer *renderer)
{
	text = loadTexture(filename,renderer);
}

void loadImages(SDL_Renderer *renderer)
{
	images["background"] = loadTexture("png/floor.png", renderer);
	images["border"] = loadTexture("png/stone_brick1.png", renderer);
	images["orc"] = loadTexture("png/orc.png", renderer);
	images["ogre"] = loadTexture("png/two_headed_ogre.png", renderer);
	images["worm"] = loadTexture("png/spiny_worm.png", renderer);
	images["hound"] = loadTexture("png/hound.png", renderer);
	images["orcWarrior"] = loadTexture("png/orc_warrior.png", renderer);
	images["orcWizard"] = loadTexture("png/orc_wizard.png", renderer);
	images["orcWarlord"] = loadTexture("png/orc_warlord.png", renderer);
	images["mace"] = loadTexture("png/mace.png", renderer);
	images["greataxe"] = loadTexture("png/greataxe.png", renderer);
	images["glaive"] = loadTexture("png/glaive3.png", renderer);
	images["handaxe"] = loadTexture("png/hand_axe.png", renderer);
	images["club"] = loadTexture("png/club_slant.png", renderer);
	images["sword"] = loadTexture("png/long_sword_slant.png", renderer);
	images["shield"] = loadTexture("png/shield_kite3.png", renderer);
	images["shieldorc"] = loadTexture("png/shield_kite4.png", renderer);

	images["fighter"] = loadTexture("png/fighter.png", renderer);
	images["barbarian"] = loadTexture("png/barbarian.png", renderer);
	images["archer"] = loadTexture("png/archer.png", renderer);
	images["rogue"] = loadTexture("png/rogue.png", renderer);
	images["cleric"] = loadTexture("png/cleric.png", renderer);
	images["wizard"] = loadTexture("png/wizard.png", renderer);
	images["textBackground"] = loadTexture("png/volcanic_floor0.png", renderer);
	images["UIBorder"] = loadTexture("png/stone_dark0.png", renderer);

	images["greatsword"] = loadTexture("png/great_sword_slant.png", renderer);
	images["staff"] = loadTexture("png/staff_mage.png", renderer);
	images["dagger"] = loadTexture("png/dagger.png", renderer);

	images["sword_inv"] = loadTexture("png/long_sword1.png", renderer);
	images["shield_inv"] = loadTexture("png/shield1_elven.png", renderer);
	images["greatsword_inv"] = loadTexture("png/greatsword2.png", renderer);
	images["bow_inv"] = loadTexture("png/longbow.png", renderer);
	images["dagger_inv"] = loadTexture("png/dagger_inv.png", renderer);
	images["cloak_inv"] = loadTexture("png/cloak2.png", renderer);
	images["staff_inv"] = loadTexture("png/staff05.png", renderer);
	images["book_inv"] = loadTexture("png/metal_blue.png", renderer);
	images["mace_inv"] = loadTexture("png/mace2.png", renderer);
}



void printRect(std::string text, SDL_Renderer * ren, int startX, int startY, int w, int h)
{
	//keep track of current width, height offset, char in string
	int maxX = startX + w; int maxY = startY + h;
	int x = startX; int y = startY;
	unsigned i = 0;
	while (i < text.size() && y + TEXT_SIZE <= maxY)
	{
		//write char
		renderTextCharacter(text[i], ren, x, y);
		i++;
		x += TEXT_SIZE;
		if (x + TEXT_SIZE > maxX)
		{
			x = startX;
			y += TEXT_SIZE;
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
}

void renderDemoSplashScreen(SDL_Renderer *renderer)
{
	//Background
	for (int x = TILE_SIZE; x < SCREEN_WIDTH - TILE_SIZE; x += TILE_SIZE)
	{
		for (int y = TILE_SIZE; y < SCREEN_HEIGHT - TILE_SIZE * 8; y += TILE_SIZE)
		{
			renderTexture(images["background"], renderer, x, y);
		}
	}
	//Text area background
	for (int x = TILE_SIZE*2; x < SCREEN_WIDTH - TILE_SIZE; x += TILE_SIZE)
	{
		for (int y = SCREEN_HEIGHT - TILE_SIZE * 7; y < SCREEN_HEIGHT - TILE_SIZE; y += TILE_SIZE)
		{
			renderTexture(images["textBackground"], renderer, x, y);
		}
	}
	//Bricks along window interior border, border between map and UI elements
	//I think this is too much of a waste of space for a real game,
	//but it looks nice enough for a demo
	for (int x = TILE_SIZE; x < SCREEN_WIDTH - TILE_SIZE; x += TILE_SIZE)
	{
		renderTexture(images["border"], renderer, x, 0);
		renderTexture(images["border"], renderer, x, SCREEN_HEIGHT - TILE_SIZE);
		//interior map area/text area border
		renderTexture(images["UIBorder"], renderer, x, SCREEN_HEIGHT - TILE_SIZE * 8);
	}
	for (int y = 0; y < SCREEN_HEIGHT; y += TILE_SIZE)
	{
		renderTexture(images["border"], renderer, 0, y);
		renderTexture(images["border"], renderer, SCREEN_WIDTH - TILE_SIZE, y);
	}

	//The party

	renderTexture(images["fighter"], renderer, SCREEN_WIDTH / 2 - TILE_SIZE, SCREEN_HEIGHT / 2 - TILE_SIZE);
	renderTexture(images["sword"], renderer, SCREEN_WIDTH / 2 - TILE_SIZE, SCREEN_HEIGHT / 2 - TILE_SIZE);
	renderTexture(images["shield"], renderer, SCREEN_WIDTH / 2 - TILE_SIZE, SCREEN_HEIGHT / 2 - TILE_SIZE);
	renderTexture(images["archer"], renderer, SCREEN_WIDTH / 2 - TILE_SIZE * 5, SCREEN_HEIGHT / 2 - TILE_SIZE * 2);
	renderTexture(images["barbarian"], renderer, SCREEN_WIDTH / 2 - TILE_SIZE * 2, SCREEN_HEIGHT / 2 - TILE_SIZE);
	renderTexture(images["greatsword"], renderer, SCREEN_WIDTH / 2 - TILE_SIZE * 2, SCREEN_HEIGHT / 2 - TILE_SIZE);
	renderTexture(images["wizard"], renderer, SCREEN_WIDTH / 2 - TILE_SIZE * 2, SCREEN_HEIGHT / 2);
	renderTexture(images["staff"], renderer, SCREEN_WIDTH / 2 - TILE_SIZE * 2, SCREEN_HEIGHT / 2);
	renderTexture(images["cleric"], renderer, SCREEN_WIDTH / 2 - TILE_SIZE * 3, SCREEN_HEIGHT / 2 + TILE_SIZE);
	renderTexture(images["mace"], renderer, SCREEN_WIDTH / 2 - TILE_SIZE * 3, SCREEN_HEIGHT / 2 + TILE_SIZE);
	renderTexture(images["rogue"], renderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	renderTexture(images["dagger"], renderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	//The orcs and their allies

	renderTexture(images["orcWarlord"], renderer, SCREEN_WIDTH / 2 + TILE_SIZE, SCREEN_HEIGHT / 2 - TILE_SIZE * 2);
	renderTexture(images["glaive"], renderer, SCREEN_WIDTH / 2 + TILE_SIZE, SCREEN_HEIGHT / 2 - TILE_SIZE * 2);

	renderTexture(images["orcWarrior"], renderer, SCREEN_WIDTH / 2 + TILE_SIZE * 2, SCREEN_HEIGHT / 2 - TILE_SIZE * 3);
	renderTexture(images["sword"], renderer, SCREEN_WIDTH / 2 + TILE_SIZE * 2, SCREEN_HEIGHT / 2 - TILE_SIZE * 3);
	renderTexture(images["shieldorc"], renderer, SCREEN_WIDTH / 2 + TILE_SIZE * 2, SCREEN_HEIGHT / 2 - TILE_SIZE * 3);
	renderTexture(images["orcWarrior"], renderer, SCREEN_WIDTH / 2 + TILE_SIZE, SCREEN_HEIGHT / 2 - TILE_SIZE * 3);
	renderTexture(images["greataxe"], renderer, SCREEN_WIDTH / 2 + TILE_SIZE,SCREEN_HEIGHT / 2 - TILE_SIZE * 3);

	renderTexture(images["orcWizard"], renderer, SCREEN_WIDTH / 2 + TILE_SIZE * 2, SCREEN_HEIGHT / 2 - TILE_SIZE * 5);

	renderTexture(images["orc"], renderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - TILE_SIZE * 3);
	renderTexture(images["mace"], renderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - TILE_SIZE * 3);

	renderTexture(images["ogre"], renderer, SCREEN_WIDTH / 2 - TILE_SIZE * 3, SCREEN_HEIGHT / 2 - TILE_SIZE * 3);

	renderTexture(images["worm"], renderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - TILE_SIZE * 5);

	renderTexture(images["orc"], renderer, SCREEN_WIDTH / 2 - TILE_SIZE, SCREEN_HEIGHT / 2 - TILE_SIZE * 4);
	renderTexture(images["handaxe"], renderer, SCREEN_WIDTH / 2 - TILE_SIZE, SCREEN_HEIGHT / 2 - TILE_SIZE * 4);

	renderTexture(images["orc"], renderer, SCREEN_WIDTH / 2 - TILE_SIZE, SCREEN_HEIGHT / 2 - TILE_SIZE * 6);
	renderTexture(images["club"], renderer, SCREEN_WIDTH / 2 - TILE_SIZE, SCREEN_HEIGHT / 2 - TILE_SIZE * 6);

	//Giant hideous poorly-scaled portrait of orc warlord on the left
	SDL_Rect portrait;
	portrait.x = TILE_SIZE; portrait.y = TILE_SIZE;
	portrait.w = TILE_SIZE * 8; portrait.h = TILE_SIZE * 11;
	renderTexture(images["orcWarlord"], renderer, portrait);
	renderTexture(images["glaive"], renderer, portrait);

	printRect("Fred,", renderer, TEXT_SIZE * 8, TEXT_SIZE * 14, TEXT_SIZE * 15, TEXT_SIZE);
	printRect("the Orc Warlord", renderer, TEXT_SIZE * 3, TEXT_SIZE * 15, TEXT_SIZE * 15, TEXT_SIZE);

	//Encounter options on the right
	printRect("Your party runs into a few orcs. What do you do?", renderer, TILE_SIZE * 18, TILE_SIZE * 2, SCREEN_WIDTH - TILE_SIZE * 19,TEXT_SIZE*4);

	printRect("1 - Try to negotiate.", renderer, TILE_SIZE * 18, TILE_SIZE * 4, SCREEN_WIDTH - TILE_SIZE * 19, TEXT_SIZE * 4);
	printRect("2 - Fight the orcs!", renderer, TILE_SIZE * 18, TILE_SIZE * 5, SCREEN_WIDTH - TILE_SIZE * 19, TEXT_SIZE * 4);
	printRect("3 - Run away!", renderer, TILE_SIZE * 18, TILE_SIZE * 6, SCREEN_WIDTH - TILE_SIZE * 19, TEXT_SIZE * 4);
	printRect("4 - Surrender.", renderer, TILE_SIZE * 18, TILE_SIZE * 7, SCREEN_WIDTH - TILE_SIZE * 19, TEXT_SIZE * 4);

	//Party info area

	//TERENCE, THE FIGHTER
	printRect(" Terence, the Fighter", renderer,
		TILE_SIZE * 2, SCREEN_HEIGHT - TILE_SIZE * 7, SCREEN_WIDTH - TILE_SIZE*6, TEXT_SIZE);
	printRect(" HP:  20/20  MP   2/3   Confident", renderer,
		TILE_SIZE * 2, SCREEN_HEIGHT - TILE_SIZE * 7 + TEXT_SIZE, SCREEN_WIDTH - TILE_SIZE * 6, TEXT_SIZE);
	renderTexture(images["fighter"], renderer, TILE_SIZE, SCREEN_HEIGHT - TILE_SIZE * 7);
	renderTexture(images["sword"], renderer, TILE_SIZE, SCREEN_HEIGHT - TILE_SIZE * 7);
	renderTexture(images["shield"], renderer, TILE_SIZE, SCREEN_HEIGHT - TILE_SIZE * 7);
	renderTexture(images["sword_inv"], renderer, SCREEN_WIDTH-TILE_SIZE*4, SCREEN_HEIGHT - TILE_SIZE * 7);
	renderTexture(images["shield_inv"], renderer, SCREEN_WIDTH - TILE_SIZE * 3, SCREEN_HEIGHT - TILE_SIZE * 7);
	//NORRIS, THE BARBARIAN
	printRect(" Norris, the Barbarian", renderer,
		TILE_SIZE * 2, SCREEN_HEIGHT - TILE_SIZE * 6, SCREEN_WIDTH - TILE_SIZE * 6, TEXT_SIZE);
	printRect(" HP:  34/34  MP   0/0   Unshakeable", renderer,
		TILE_SIZE * 2, SCREEN_HEIGHT - TILE_SIZE * 6 + TEXT_SIZE, SCREEN_WIDTH - TILE_SIZE * 6, TEXT_SIZE);
	renderTexture(images["barbarian"], renderer, TILE_SIZE, SCREEN_HEIGHT - TILE_SIZE * 6);
	renderTexture(images["greatsword"], renderer, TILE_SIZE, SCREEN_HEIGHT - TILE_SIZE * 6);
	renderTexture(images["greatsword_inv"], renderer, SCREEN_WIDTH - TILE_SIZE * 4, SCREEN_HEIGHT - TILE_SIZE * 6);
	//NESSUS, THE ARCHER
	printRect(" Nessus, the Archer", renderer,
		TILE_SIZE * 2, SCREEN_HEIGHT - TILE_SIZE * 5, SCREEN_WIDTH - TILE_SIZE * 6, TEXT_SIZE);
	printRect(" HP:  18/18  MP   1/1   Steady", renderer,
		TILE_SIZE * 2, SCREEN_HEIGHT - TILE_SIZE * 5 + TEXT_SIZE, SCREEN_WIDTH - TILE_SIZE * 6, TEXT_SIZE);
	renderTexture(images["archer"], renderer, TILE_SIZE, SCREEN_HEIGHT - TILE_SIZE * 5);
	renderTexture(images["bow_inv"], renderer, SCREEN_WIDTH - TILE_SIZE * 4, SCREEN_HEIGHT - TILE_SIZE * 5);
	//MAURICE, THE ROGUE
	printRect(" Maurice, the Rogue", renderer,
		TILE_SIZE * 2, SCREEN_HEIGHT - TILE_SIZE * 4, SCREEN_WIDTH - TILE_SIZE * 6, TEXT_SIZE);
	printRect(" HP:  14/14  MP   6/11  Self-certain", renderer,
		TILE_SIZE * 2, SCREEN_HEIGHT - TILE_SIZE * 4 + TEXT_SIZE, SCREEN_WIDTH - TILE_SIZE * 6, TEXT_SIZE);
	renderTexture(images["rogue"], renderer, TILE_SIZE, SCREEN_HEIGHT - TILE_SIZE * 4);
	renderTexture(images["dagger"], renderer, TILE_SIZE, SCREEN_HEIGHT - TILE_SIZE * 4);
	renderTexture(images["dagger_inv"], renderer, SCREEN_WIDTH - TILE_SIZE * 4, SCREEN_HEIGHT - TILE_SIZE * 4);
	renderTexture(images["cloak_inv"], renderer, SCREEN_WIDTH - TILE_SIZE * 3, SCREEN_HEIGHT - TILE_SIZE * 4);
	//MENNAS, THE CLERIC
	printRect(" Mennas, the Cleric", renderer,
		TILE_SIZE * 2, SCREEN_HEIGHT - TILE_SIZE * 3, SCREEN_WIDTH - TILE_SIZE * 6, TEXT_SIZE);
	printRect(" HP:  17/17  MP  14/18  Zealous", renderer,
		TILE_SIZE * 2, SCREEN_HEIGHT - TILE_SIZE * 3 + TEXT_SIZE, SCREEN_WIDTH - TILE_SIZE * 6, TEXT_SIZE);
	renderTexture(images["cleric"], renderer, TILE_SIZE, SCREEN_HEIGHT - TILE_SIZE * 3);
	renderTexture(images["mace"], renderer, TILE_SIZE, SCREEN_HEIGHT - TILE_SIZE * 3);
	renderTexture(images["mace_inv"], renderer, SCREEN_WIDTH - TILE_SIZE * 4, SCREEN_HEIGHT - TILE_SIZE * 3);
	renderTexture(images["book_inv"], renderer, SCREEN_WIDTH - TILE_SIZE * 3, SCREEN_HEIGHT - TILE_SIZE * 3);
	//BORIS, THE WIZARD
	printRect(" Boris, the Wizard", renderer,
		TILE_SIZE * 2, SCREEN_HEIGHT - TILE_SIZE * 2, SCREEN_WIDTH - TILE_SIZE * 6, TEXT_SIZE);
	printRect(" HP:   9/9   MP  24/29  Focused", renderer,
		TILE_SIZE * 2, SCREEN_HEIGHT - TILE_SIZE * 2 + TEXT_SIZE, SCREEN_WIDTH - TILE_SIZE * 6, TEXT_SIZE);
	renderTexture(images["wizard"], renderer, TILE_SIZE, SCREEN_HEIGHT - TILE_SIZE * 2);
	renderTexture(images["staff"], renderer, TILE_SIZE, SCREEN_HEIGHT - TILE_SIZE * 2);
	renderTexture(images["staff_inv"], renderer, SCREEN_WIDTH - TILE_SIZE * 4, SCREEN_HEIGHT - TILE_SIZE * 2);

	

	SDL_RenderPresent(renderer);
}
