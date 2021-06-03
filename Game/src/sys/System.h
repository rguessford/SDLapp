#pragma once
#include<core/Renderer.h>
#include<entt/entity/registry.hpp>
class System
{
public:
	explicit System(entt::registry& registry, Renderer& renderer) : mRegistry(registry), mRenderer(renderer) {}

	virtual void update(float dt) {};

	static void setPause(bool pause) { sPause = pause; }

protected:
	entt::registry& mRegistry;
	Renderer& mRenderer;
	inline static bool sPause = false;
};