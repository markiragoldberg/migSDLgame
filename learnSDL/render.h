#pragma once
#include <iostream>
#include <ostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <unordered_map>

const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 640;
const int TILE_SIZE = 32;
const int TEXT_SIZE = 16;

/**
* Loads a BMP image into a texture on the rendering device
* @param file The BMP image file to load
* @param ren The renderer to load the texture onto
* @return the loaded texture, or nullptr if something went wrong.
*/
SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren);

/**
* Draw an SDL_Texture to an SDL_Renderer at some destination rect
* taking a clip of the texture if desired
* @param tex The source texture we want to draw
* @param ren The renderer we want to draw to
* @param dst The destination rectangle to render the texture to
* @param clip The sub-section of the texture to draw (clipping rect)
*		default of nullptr draws the entire texture
*/
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, SDL_Rect dst, SDL_Rect *clip = nullptr);
/**
* Draw an SDL_Texture to an SDL_Renderer at position x, y, preserving
* the texture's width and height and taking a clip of the texture if desired
* If a clip is passed, the clip's width and height will be used instead of
*	the texture's
* @param tex The source texture we want to draw
* @param ren The renderer we want to draw to
* @param x The x coordinate to draw to
* @param y The y coordinate to draw to
* @param clip The sub-section of the texture to draw (clipping rect)
*		default of nullptr draws the entire texture
*/
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, SDL_Rect *clip = nullptr);

void renderTextCharacter(char character, SDL_Renderer *ren, int x, int y);

//Loads the text file used for rendering strings
//Currently basically only works with very specific type of libtcod character graphics file
void loadText(std::string filename, SDL_Renderer *renderer);

//Loads the images currently hardcoded into use
//Should eventually load images requested by entries in data files (sword object asks for "sword.png", etc.)
void loadImages(SDL_Renderer *renderer);

void printRect(std::string, SDL_Renderer * ren, int x, int y, int w, int h);

/**
* Log an SDL error with some error message to the output stream of our choice
* @param os The output stream to write the message to
* @param msg The error message to write, format will be msg error: SDL_GetError()
*/
void logSDLError(std::ostream &os, const std::string &msg);

void deleteRenderingStuff();

void renderDemoSplashScreen(SDL_Renderer *ren);


