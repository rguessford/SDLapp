#include "CameraSystem.h"
#include<comp/actorComponents.h>
#include <util/isomath.h>

CameraSystem::CameraSystem(entt::registry& registry) : System(registry){}

void CameraSystem::update(double dt) {
	mRegistry.view<camera, position>().each([&](auto& camera, auto& position) {
		camera.xOffset = -position.x;
		camera.yOffset = -position.y;
		twoDToIso(camera.xOffset, camera.yOffset);
		camera.xOffset = camera.xOffset + camera.baseXOffset;
		camera.yOffset = camera.yOffset + camera.baseYOffset;
	});
}
