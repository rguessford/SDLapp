#pragma once
#include "System.h"
class CameraSystem :
    public System
{
public:
    CameraSystem(entt::registry& registry);
    void update(double dt);
};

