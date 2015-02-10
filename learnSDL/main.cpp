#include <iostream>
#include <SDL.h>
#include "render.h"
//SDL eats paste
#undef main

int main()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		logSDLError(std::cout, "SDL_Init");
		return 1;
	}

	SDL_Window *window = SDL_CreateWindow("SDL2", 100, 30, SCREEN_WIDTH,
		SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr){
		logSDLError(std::cout, "CreateWindow");
		SDL_Quit();
		return 1;
	}
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr){
		logSDLError(std::cout, "CreateRenderer");
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	SDL_SetRenderDrawColor(renderer, 0, 0, 0,255);
	SDL_RenderClear(renderer);

	loadText("dejavu16x16_gs_tc_ts.png", renderer);
	loadImages(renderer);
	renderDemoSplashScreen(renderer);

	int hackyWayToGetTheGameWindowToPauseUntilInput;
	std::cin >> hackyWayToGetTheGameWindowToPauseUntilInput;

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	deleteRenderingStuff();
	SDL_Quit();
	return 0;
}
