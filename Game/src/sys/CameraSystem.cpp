#include "CameraSystem.h"
#include<comp/actorComponents.h>
#include <util/isomath.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 
CameraSystem::CameraSystem(entt::registry& registry) : System(registry), worldUp(0.f,1.f,0.f){}

void CameraSystem::update(double dt, glm::mat4& viewMatrix) {
	mRegistry.view<cameraFocus, position>().each([&](auto& cameraFocus, auto& position) {
		cameraFocus.vec3.x = position.vec3.x + 10.f;
		cameraFocus.vec3.y = position.vec3.y + 8.14f;
		cameraFocus.vec3.z = position.vec3.z + 10.f;
		viewMatrix = glm::lookAt(cameraFocus.vec3,
								position.vec3,
								worldUp);
	});
}
