#include "core/SDLApplication.h"
#include "Window.h"
#include "core/Renderer.h"
#include "Events.h"
#include "Components.h"
#include "entityFactories.h"


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

		entt::entity tilemapEntity = makeDefaultTilemap(registry, &renderer);
		auto tileMapView = registry.view<tileMapRenderer, spriteSheet>();
		auto& mapTable= tileMapView.get<tileMapRenderer>(tilemapEntity);

		int counter=0;

		while (events.handleEvents()) {
			counter++;
			renderer.clearScreen(0, 0, 0, 0);

			for (auto entity : tileMapView) {
				auto& mapRenderer = tileMapView.get<tileMapRenderer>(entity);
				auto& ss = tileMapView.get<spriteSheet>(entity);

				for (int i = 0; i < 20; i++) {
					for (int j = 0; j < 20; j++) {
						mapTable.tileMap[j][i] = (j+(counter/100)) % 34;
						SDL_Rect renderquad = { i*32+800,j*32,64,64 };
						renderer.twoDToIso(&renderquad);
						
						SDL_RenderCopy(renderer, ss.texture, &ss.frameMapping.at(mapRenderer.tileMap[j][i]) , &renderquad);
					}
				}
				

			}

			renderer.update();
		}

		registry.destroy(tilemapEntity);
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