#include "SDLApplication.h"

#include <SDL_image.h>
#include<sstream>
#include<SDL.h>

SDLApplication::SDLApplication() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::stringstream buffer;
		buffer << "Could not initialize SDL properly: " << SDL_GetError();

		throw std::runtime_error(buffer.str());
	}

	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		std::stringstream buffer;
		buffer << "SDL_image could not initialize! SDL_image Error: ", IMG_GetError();

		throw std::runtime_error(buffer.str());
	}
}

SDLApplication::~SDLApplication() {
	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}
