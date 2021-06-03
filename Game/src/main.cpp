#include "core/SDLApplication.h"
#include "core/Window.h"
#include "core/Renderer.h"
#include "core/Events.h"

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

		makeDefaultTilemap(registry, renderer);
		
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

//int main(int argc, char* args[]) {
//	int counter = 0;
//	int m;
//	int n;
//	std::cout << "rows";
//	std::cin >> m;
//	std::cout << "cols";
//	std::cin >> n;
//
//
//
//	std::unique_ptr < std::unique_ptr<int[] >[]> multi;
//	multi = std::make_unique<std::unique_ptr<int[]>[]>(m);
//	for (int i = 0; i < m; i++) {
//		multi[i] = std::make_unique<int[]>(n);
//	}
//
//	for (int i = 0; i < m; i++) {
//		for (int j = 0; j < n; j++) {
//
//			// Assign values to the
//			// memory blocks created
//			multi[i][j] = ++counter;
//		}
//	}
//
//	// Traverse the 2D array
//	for (int i = 0; i < m; i++) {
//		for (int j = 0; j < n; j++) {
//
//			// Print the values of
//			// memory blocks created
//			std::cout << multi[i][j] << " ";
//		}
//		std::cout << std::endl;
//	}
//	return 0;
//}