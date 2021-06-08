#pragma once
#include "System.h"
class CameraSystem :
    public System
{
    int mBaseXOffset = 0;
    int mBaseYOffset = 0;
public:
    CameraSystem(int x, int y, entt::registry& registry);
    void update(double dt);
};

