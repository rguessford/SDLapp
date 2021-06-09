#pragma once
#include "core/TextureCache.h"
#include "core/AnimationRepository.h"
#include "comp/actorComponents.h"
#include <entt/entity/registry.hpp>

entt::entity makeTilemap(entt::registry&, TextureCache&);
entt::entity makeZombie(int, int, entt::registry&, TextureCache&, AnimationRepository&, camera camera = {0,0});