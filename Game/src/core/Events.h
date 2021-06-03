#pragma once
#include "SDL.h"

class Events
{
public:
	bool handleEvents();


private:
	SDL_Event event;
};
