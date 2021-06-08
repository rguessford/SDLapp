#pragma once
#include "SDL.h"
#include<entt/entity/registry.hpp>

class Events
{
public:
	bool handleEvents(double dt, entt::registry&);


private:
	SDL_Event event;
};
