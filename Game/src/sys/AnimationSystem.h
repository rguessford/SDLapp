#pragma once
#include "System.h"
#include "comp/textureComponents.h"
class AnimationSystem :
    public System
{
public:
    AnimationSystem(entt::registry&);
    void update(double dt);
};

