#include "core/SDLApplication.h"
#include "core/Window.h"
#include "core/Renderer.h"
#include "core/Events.h"
#include "core/textureCache.h"

#include "util/entityFactories.h"
#include "sys/TileManager.h"

#include <iostream>
#include <entt/entity/registry.hpp>

#include <SDL.h>

const int SCREEN_WIDTH = 1600;
const int SCREEN_HEIGHT = 1440;

int main(int argc, char* args[])
{

	try {
		SDLApplication application;
		Window window(SCREEN_WIDTH, SCREEN_HEIGHT);
		Renderer renderer(window);
		Events events;
		entt::registry registry;
		TextureCache textureCache(renderer);
		makeTilemap(registry, textureCache);
		

		TileManager tileManager(registry, renderer);
		unsigned int lastTime = 0, currentTime, deltaTime;
		while (events.handleEvents()) {
			currentTime = SDL_GetTicks();
			deltaTime = currentTime - lastTime;
			renderer.clearScreen(0, 0, 0, 0);
			tileManager.update(deltaTime);
			renderer.update();
		}
	}
	catch (std::exception const& e) {
		std::cerr << e.what() << "\n";
	}
	return 0;
}
