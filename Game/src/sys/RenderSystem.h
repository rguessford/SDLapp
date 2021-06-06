#pragma once
#include "sys/System.h"

class RenderSystem : System {
	public:
		RenderSystem(entt::registry& registry, Renderer& renderer);
		void update(float dt);
};