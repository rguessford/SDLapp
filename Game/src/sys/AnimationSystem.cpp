#include "AnimationSystem.h"
#include "comp/textureComponents.h"
#include "comp/commandComponents.h"
#include "core/TextureCache.h"

#include <entt/entity/registry.hpp>



AnimationSystem::AnimationSystem(entt::registry& registry) : System(registry) {}

void AnimationSystem::update(double dt)
 {
	mRegistry.view<drawable, animation>().each([&](auto entity, auto& drawable, auto& animation) {
		switch (drawable.textureDetails->name) {
		case textureNameEnum::ZOMBIE_0:
			//flags to play entire animation?
			// animation length in s?
			animation.animationTimer += dt;
			//based on other states of a zombie's components, 
			//set current animation direction, and id
			//check if the curent animation should be playing. if not, reset currentFrame
			animation.currentAnimationId = IDLE;
			auto moveComp = mRegistry.try_get<moveCommand>(entity);
			if (moveComp) {
				animation.currentAnimationId = WALK;
				float angle = std::atan2(moveComp->dir(1), moveComp->dir(0));
				//snap the angle to the closest 8-direction value 0-7 w-sw clockwise
				animation.animationDirection = (int)std::round(8 * angle / (2 * M_PI) + 13) % 8;
			}
			if (animation.prevAnim == animation.currentAnimationId && animation.prevDir == animation.animationDirection) {
				//advance frame
				if (animation.animationTimer > animation.animationLength) {
					animation.currentFrame = (animation.currentFrame + 1) % (*animation.animations)[animation.currentAnimationId].size();
					animation.animationTimer = 0.0f;
				}
			} else {
				animation.currentFrame = 0;
				animation.prevDir = animation.animationDirection;
				animation.prevAnim = animation.currentAnimationId;
			}
			

			//then use those to find the right frame to write to the drawable component
			
			drawable.currentFrame = (int)animation.animationDirection * animation.animationDirectionOffset + (*animation.animations)[animation.currentAnimationId][animation.currentFrame];
		}
		});
}
