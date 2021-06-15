#pragma once
#include "System.h"
#include "comp/commandComponents.h"
#include "comp/actorComponents.h"

class MovementSystem : System
{
public:
    MovementSystem(entt::registry& registry);
    void update(double dt);
};

