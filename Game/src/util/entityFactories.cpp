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
	reg.emplace<tileMapRenderer>(tilemapEntity, 100, 100);
	return tilemapEntity;
}

entt::entity makeZombie(entt::registry& reg, TextureCache& texCache) {
	auto zombie = reg.create();
	reg.emplace<drawable>(zombie, texCache.getTexture(textureNameEnum::ZOMBIE_0), 0);
	reg.emplace<position>(zombie, 0, 0, 0);

	return zombie;
}