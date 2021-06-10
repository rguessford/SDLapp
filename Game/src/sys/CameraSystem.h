#pragma once
#include "System.h"
class CameraSystem :
    public System
{
    float mBaseXOffset = 0;
    float mBaseYOffset = 0;
public:
    CameraSystem(float x, float y, entt::registry& registry);
    void update(double dt);
};

