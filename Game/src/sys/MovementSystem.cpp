#include "MovementSystem.h"
#include <iostream>
#include <Eigen/Dense>


MovementSystem::MovementSystem(entt::registry& registry) : System(registry) {}

void MovementSystem::update(double dt)
{
	mRegistry.view<moveCommand, position, stats>().each([&](auto entity, auto& moveCom, auto& pos, auto& statsComponent) {
		pos.vec3.x += (float)moveCom.dir(0) * statsComponent.movespeed * (float)dt;
		pos.vec3.z += (float)moveCom.dir(1) * statsComponent.movespeed * (float)dt;
		std::cout << pos.vec3.x << "," << pos.vec3.y << "," << pos.vec3.z << std::endl;
		mRegistry.remove<moveCommand>(entity);
		}); 
}
