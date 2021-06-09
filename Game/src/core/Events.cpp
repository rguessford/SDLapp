#include "Events.h"
#include "comp/actorComponents.h"
#include<iostream>
bool Events::handleEvents(double dt, entt::registry& reg)
{
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			return false;
	}
    reg.view<keyboardController, position>().each([&](position& pos) {
        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
        if (currentKeyStates[SDL_SCANCODE_UP])
        {
            pos.y-=2;
        }
        else if (currentKeyStates[SDL_SCANCODE_DOWN])
        {
            pos.y+=2;
        }
        else if (currentKeyStates[SDL_SCANCODE_LEFT])
        {
            pos.x-=2;
        }
        else if (currentKeyStates[SDL_SCANCODE_RIGHT])
        {
            pos.x+=2;
        }
    });
	return true;
}
