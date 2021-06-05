#pragma once
#include "sys/System.h"
#include <entt/entity/registry.hpp>
class TileManager :
	public System
{
public:
	void update(float dt);
	TileManager(entt::registry&, Renderer&);
};