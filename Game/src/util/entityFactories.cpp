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
	reg.emplace<drawable>(tilemapEntity, texCache.getTexture(textureNameEnum::CUBES), 0);
	reg.emplace<tileMapRenderer>(tilemapEntity, 10000, 10000);
	return tilemapEntity;
}

entt::entity makeZombie(int x, int y, entt::registry& reg, TextureCache& texCache, AnimationRepository& animRepo, camera cam = { 0,0 }) {
	auto zombie = reg.create();
	reg.emplace<drawable>(zombie, texCache.getTexture(textureNameEnum::ZOMBIE_0), 0);
	reg.emplace<position>(zombie, static_cast<float>(x), static_cast<float>(y), 0.0f);
	reg.emplace<animation>(zombie, 0, direction::W, 0, animRepo.getAnimation(animationEnum::ZOMBIE_0), 36, false, 0.0, 0.250);
	if (cam.xOffset + cam.yOffset != 0) {
		reg.emplace<keyboardController>(zombie);
		auto& newcam = reg.emplace<camera>(zombie);
		newcam.xOffset = cam.xOffset;
		newcam.yOffset = cam.yOffset;
	}
	return zombie;
}
