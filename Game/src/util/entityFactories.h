#pragma once
#include "core/Renderer.h"
#include <entt/entity/registry.hpp>

entt::entity makeTilemap(entt::registry&, Renderer&);

std::string loadJsonSpritesheetManifest(std::vector<SDL_Rect>&, std::string);