#pragma once

struct TextureDetails;

#include "core/TextureCache.h"

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

struct drawable {
	//i would have liked to just use the textureDetails themselves as components but components get destroyed
	std::shared_ptr<TextureDetails> texutreDetails;
	int currentFrame;
};

enum zombieAnimationEnum {
	IDLE,
	WALK,
	ATTACK,
	ATTACK2,
	BLOCK,
	DEATH,
	DEATH2
};

enum class direction {
	W, NW, N, NE, E, SE, S, SW
};

struct animation {
	int currentAnimationId;
	int animationDirection;

	//current frame needs to be bounded by animations.[animationEnum].size
	std::shared_ptr<std::vector<std::vector<int>>> animations;
	int animationDirectionOffset = 0;

};

//for static sprites, specify a default framemapping
//animation component to control which frame to render