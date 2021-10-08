#pragma once
#include "core/TextureCache.h"
#include "core/AnimationRepository.h"
#include "comp/actorComponents.h"
#include <entt/entity/registry.hpp>

entt::entity makeTilemap(entt::registry&, TextureCache&);
entt::entity makeZombie(int, int, entt::registry&, TextureCache&, AnimationRepository&);
entt::entity makeThing(entt::registry&, float, float, float);