#include "Events.h"
#include "comp/actorComponents.h"
#include "comp/commandComponents.h"

bool Events::handleEvents(double dt, entt::registry& reg)
{
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			return false;
	}
    reg.view<keyboardController, position>().each([&](entt::entity entity, position& pos) {
        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
        if (currentKeyStates[SDL_SCANCODE_UP])
        {
            reg.emplace<moveCommand>(entity, -1.f+ currentKeyStates[SDL_SCANCODE_RIGHT], -1.f+ currentKeyStates[SDL_SCANCODE_LEFT]);
        }
        else if (currentKeyStates[SDL_SCANCODE_DOWN])
        {
           reg.emplace<moveCommand>(entity, 1.f-currentKeyStates[SDL_SCANCODE_LEFT], 1.f - currentKeyStates[SDL_SCANCODE_RIGHT]);
        }
        else if (currentKeyStates[SDL_SCANCODE_LEFT])
        {
            reg.emplace<moveCommand>(entity, -1.f+ currentKeyStates[SDL_SCANCODE_DOWN], 1.f - currentKeyStates[SDL_SCANCODE_UP]);
        }
        else if (currentKeyStates[SDL_SCANCODE_RIGHT])
        {
            reg.emplace<moveCommand>(entity, 1.f - currentKeyStates[SDL_SCANCODE_UP], -1.f + currentKeyStates[SDL_SCANCODE_DOWN]);
        }
    });
	return true;
}
