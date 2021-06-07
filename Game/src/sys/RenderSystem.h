#pragma once
#include "sys/System.h"

class RenderSystem : System {
	Renderer& mRenderer;
	public:
		RenderSystem(entt::registry& registry, Renderer& renderer);
		void update(float dt);
};