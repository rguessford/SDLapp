#include "CameraSystem.h"
#include<comp/actorComponents.h>
#include <util/isomath.h>

CameraSystem::CameraSystem(float x, float y, entt::registry& registry) : System(registry), mBaseXOffset(x), mBaseYOffset(y){}

void CameraSystem::update(double dt) {
	mRegistry.view<camera, position>().each([&](auto& camera, auto& position) {
		camera.xOffset = -position.x;
		camera.yOffset = -position.y;
		twoDToIso(camera.xOffset, camera.yOffset);
		camera.xOffset = camera.xOffset + mBaseXOffset;
		camera.yOffset = camera.yOffset + mBaseYOffset;
	});
}
