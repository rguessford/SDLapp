#include "entityFactories.h"

#include "comp/actorComponents.h"
#include "comp/textureComponents.h"

#include <rapidjson/document.h>
#include <iostream>
#include <memory>
#include <vector>

//creates an entity to represent and draw a tilemap
entt::entity makeTilemap(entt::registry& reg, TextureCache& texCache)
{
	//json is used as the spritesheet manifest
	auto tilemapEntity = reg.create();
	reg.emplace<drawable>(tilemapEntity, texCache.getTexture(textureNameEnum::CUBES), 0, false);
	//tilemap doesn't use a position, but every entity with a drawable needs a position. shrug.
	reg.emplace<position>(tilemapEntity, 0.0f, 0.0f, 0.0f);
	auto& mapRenderer = reg.emplace<tileMapRenderer>(tilemapEntity, 100, 100);
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			mapRenderer.tileMap[j][i] = (i + j) % 34;
		}
	}
	return tilemapEntity;
}

entt::entity makeZombie(int x, int y, entt::registry& reg, TextureCache& texCache, AnimationRepository& animRepo, camera cam) {
	auto zombie = reg.create();
	reg.emplace<drawable>(zombie, texCache.getTexture(textureNameEnum::ZOMBIE_0), 0);
	reg.emplace<position>(zombie, static_cast<float>(x), static_cast<float>(y), 0.0f);
	reg.emplace<animation>(zombie, 0, rand()%8, 0, animRepo.getAnimation(animationEnum::ZOMBIE_0), 36, 0.0, 0.250);
	if (cam.xOffset + cam.yOffset != 0) {
		reg.emplace<keyboardController>(zombie);
		auto& newcam = reg.emplace<camera>(zombie);
		newcam.xOffset = cam.xOffset;
		newcam.yOffset = cam.yOffset;
	}
	return zombie;
}
