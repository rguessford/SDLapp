#pragma once
#include <cstddef>
#include <stdlib.h>  
#include <memory>
#include <map>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>

struct tileMapRenderer {
	std::unique_ptr<std::unique_ptr<int[]>[]> tileMap;
	//height is rows, width is cols
	tileMapRenderer(int width, int height) {
		tileMap = std::make_unique<std::unique_ptr<int[]>[]>(height);
		for (int i = 0; i < height; i++) {
			tileMap[i] = std::make_unique<int[]>(width);
		}
	}
};

enum spriteSheetNameEnum {
	CUBES,ZOMBIE_0
};

struct spriteSheet {
	spriteSheetNameEnum name;
	SDL_Texture* texture;
	std::shared_ptr<std::vector<SDL_Rect>> frameMapping;
	int size;
//for static sprites, specify a default framemapping
//animation component to control which frame to render
};
