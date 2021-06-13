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
	//wow what is this? refactor this to use vectors.
	std::unique_ptr<std::unique_ptr<int[]>[]> tileMap;
	tileMapRenderer(int width, int height) {
		tileMap = std::make_unique<std::unique_ptr<int[]>[]>(height);
		for (int i = 0; i < height; i++) {
			tileMap[i] = std::make_unique<int[]>(width);
		}
	}
};

struct drawable {
	std::shared_ptr<TextureDetails> textureDetails;
	int currentFrame;
};

//empty component marking entites for z ordering
struct visible{};

enum zombieAnimationEnum {
	IDLE,
	WALK,
	ATTACK,
	ATTACK2,
	BLOCK,
	DEATH,
	DEATH2
};

enum direction {
	W, NW, N, NE, E, SE, S, SW
};

struct animation {
	int currentAnimationId;
	int animationDirection;
	int currentFrame;
	
	//current frame needs to be bounded by animations.[animationEnum].size
	std::shared_ptr<std::vector<std::vector<int>>> animations;

	//number of frames per direction
	int animationDirectionOffset = 0;

	//animation lengths per animation needed
	double animationTimer;
	double animationLength;

	int prevAnim = currentAnimationId; // placeholder
	int prevDir = animationDirection;
};

//for static sprites, specify a default framemapping
//animation component to control which frame to render