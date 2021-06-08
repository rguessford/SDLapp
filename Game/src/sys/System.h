#pragma once
#include<core/Renderer.h>
#include<entt/entity/registry.hpp>
class System
{
public:
	explicit System(entt::registry& registry) : mRegistry(registry) {}

	virtual void update(double dt) {};

	static void setPause(bool pause) { sPause = pause; }

protected:
	entt::registry& mRegistry;
	
	inline static bool sPause = false;
};
