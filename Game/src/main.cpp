#include "core/SDLApplication.h"
#include "core/Window.h"
#include "core/Renderer.h"
#include "core/Events.h"
#include "core/textureCache.h"

#include "util/entityFactories.h"
#include "sys/TileManager.h"
#include "sys/RenderSystem.h"
#include "sys/AnimationSystem.h"

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
		AnimationRepository animationRepository;

		makeTilemap(registry, textureCache);
		makeZombie(registry, textureCache, animationRepository);

		RenderSystem renderSystem(registry, renderer);
		AnimationSystem animationSystem(registry);

		TileManager tileManager(registry, renderer);
		float lastTime = 0.0f, currentTime, deltaTime;
		while (events.handleEvents()) {
			currentTime = SDL_GetTicks();
			deltaTime = currentTime - lastTime;
			lastTime = currentTime;
			renderer.clearScreen(0, 0, 0, 0);
			tileManager.update(deltaTime);
			animationSystem.update(deltaTime);
			renderSystem.update(deltaTime);
			renderer.update();
		}
	}
	catch (std::exception const& e) {
		std::cerr << e.what() << "\n";
	}
	return 0;
}
