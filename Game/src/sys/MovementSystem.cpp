#include "MovementSystem.h"
#include <iostream>
#include <Eigen/Dense>

MovementSystem::MovementSystem(entt::registry& registry) : System(registry) {}

void MovementSystem::update(double dt)
{
	mRegistry.view<moveCommand, position, stats>().each([&](auto entity, auto& moveCom, auto& pos, auto& statsComponent) {
		pos.x += (float)moveCom.dir(0) * statsComponent.movespeed * (float)dt;
		pos.y += (float)moveCom.dir(1) * statsComponent.movespeed * (float)dt;
		mRegistry.remove<moveCommand>(entity);
		}); 
}
