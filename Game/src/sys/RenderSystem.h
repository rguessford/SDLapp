#pragma once
#include "sys/System.h"

class RenderSystem : System {
	Renderer& mRenderer;
	int fpsCounter;
	double fpsTimer;
	public:
		RenderSystem(entt::registry& registry, Renderer& renderer);
		void update(double dt);
};