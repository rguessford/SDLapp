#include "MovementSystem.h"
#include <iostream>

MovementSystem::MovementSystem(entt::registry& registry) : System(registry) {}

void MovementSystem::update(double dt)
{
	mRegistry.view<moveCommand, position, stats>().each([&](auto entity, auto& moveCom, auto& pos, auto& statsComponent) {
		pos.x += (float)moveCom.dir(0) * statsComponent.movespeed * dt;
		pos.y += (float)moveCom.dir(1) * statsComponent.movespeed * dt;
		mRegistry.remove<moveCommand>(entity);
		});
}
