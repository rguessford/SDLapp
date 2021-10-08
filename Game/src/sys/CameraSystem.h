#pragma once
#include "System.h"
#include <glm/glm.hpp>

class CameraSystem :
    public System
{
    glm::vec3 worldUp;
public:
    CameraSystem(entt::registry& registry);
    void update(double dt, glm::mat4& viewMatrix);
};

