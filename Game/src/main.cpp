#include "core/SDLApplication.h"
#include "core/Window.h"
#include "core/Renderer.h"
#include "core/Events.h"
#include "core/textureCache.h"

#include "util/entityFactories.h"
#include "sys/TileManager.h"
#include "sys/RenderSystem.h"
#include "sys/AnimationSystem.h"
#include "sys/CameraSystem.h"
#include "comp/actorComponents.h"

#include <iostream>
#include <entt/entity/registry.hpp>
#include <chrono>
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
		std::chrono::steady_clock;

		camera cam = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };

		makeTilemap(registry, textureCache);
		makeZombie(0,0,registry, textureCache, animationRepository, cam);

		RenderSystem renderSystem(registry, renderer);
		AnimationSystem animationSystem(registry);
		CameraSystem cameraSystem(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 , registry);

		TileManager tileManager(registry, renderer);
		std::chrono::steady_clock::time_point lastTime = std::chrono::steady_clock::now(), currentTime;
		std::chrono::duration<double> deltaTime;
		while (events.handleEvents(deltaTime.count(), registry)) {
			currentTime = std::chrono::steady_clock::now();
			deltaTime = std::chrono::duration_cast<std::chrono::duration<double>>(currentTime - lastTime);
			lastTime = currentTime;
			renderer.clearScreen(0, 0, 0, 0);
			cameraSystem.update(deltaTime.count());
			tileManager.update(deltaTime.count());
			animationSystem.update(deltaTime.count());
			renderSystem.update(deltaTime.count());
			renderer.update();
		}
	}
	catch (std::exception const& e) {
		std::cerr << e.what() << "\n";
	}
	return 0;
}
