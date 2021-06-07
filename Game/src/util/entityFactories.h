#pragma once
#include "core/TextureCache.h"
#include "core/AnimationRepository.h"
#include <entt/entity/registry.hpp>

entt::entity makeTilemap(entt::registry&, TextureCache&);
entt::entity makeZombie(entt::registry&, TextureCache&, AnimationRepository&);