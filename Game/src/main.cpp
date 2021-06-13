#include "core/SDLApplication.h"
#include "core/Window.h"
#include "core/Renderer.h"
#include "core/Events.h"
#include "core/textureCache.h"

#include "util/entityFactories.h"
#include "sys/RenderSystem.h"
#include "sys/AnimationSystem.h"
#include "sys/CameraSystem.h"
#include "comp/actorComponents.h"

#include <iostream>
#include <entt/entity/registry.hpp>
#include <chrono>
#include <SDL.h>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 1024;

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

		camera cam = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };

		makeTilemap(registry, textureCache);
		makeZombie(0,0,registry, textureCache, animationRepository, cam);
		
		for (int i = 0; i < 100; i++) {
			for (int j = 0; j < 100; j++) {
				makeZombie(i*32, j*32, registry, textureCache, animationRepository);
			}
		}
		

		RenderSystem renderSystem(registry, renderer);
		AnimationSystem animationSystem(registry);
		CameraSystem cameraSystem(registry);


		std::chrono::steady_clock::time_point lastTime = std::chrono::steady_clock::now(), currentTime;
		std::chrono::duration<double> deltaTime;
		while (events.handleEvents(deltaTime.count(), registry)) {
			currentTime = std::chrono::steady_clock::now();
			deltaTime = std::chrono::duration_cast<std::chrono::duration<double>>(currentTime - lastTime);
			lastTime = currentTime;
			renderer.clearScreen(0, 0, 0, 0);
			cameraSystem.update(deltaTime.count());
			animationSystem.update(deltaTime.count());
			//animationSystem comes before movement system. 
			
			//animationsystem relies on the presence of command components and the movement system removes those.
			renderSystem.update(deltaTime.count());
			renderer.update();
		}
	}
	catch (std::exception const& e) {
		std::cerr << e.what() << "\n";
	}
	return 0;
}
