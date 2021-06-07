#include "AnimationSystem.h"
#include "comp/textureComponents.h"
#include "core/TextureCache.h"
#include <iostream>
#include <iomanip>

AnimationSystem::AnimationSystem(entt::registry& registry) : System(registry) {}

void AnimationSystem::update(float dt)
{
	mRegistry.view<drawable, animation>().each([&](auto& drawable, auto& animation) {
		switch (drawable.textureDetails->name) {
		case textureNameEnum::ZOMBIE_0:
			//flags to play entire animation?
			// animation length in s?
			animation.animationTimer += dt;
			//based on other states of a zombie's components, 
			//set current animation direction, and id
			//check if the curent animation should be playing. if not, reset currentFrame
			animation.currentAnimationId = WALK;

			if (animation.prevState) {
				//advance frame
				if (animation.animationTimer > animation.animationLength) {
					animation.currentFrame = (animation.currentFrame + 1) % (*animation.animations)[animation.currentAnimationId].size();
					animation.animationTimer = 0.0f;
				}
				// turn direction
				if (!animation.currentFrame && animation.animationTimer ==0.0f) {
					animation.animationDirection = (animation.animationDirection+1) % 8;
				}
			} else {
				animation.currentFrame = 0;
				animation.prevState = true;
			}
			

			//then use those to find the right frame to write to the drawable component
			
			drawable.currentFrame = (int)animation.animationDirection * animation.animationDirectionOffset + (*animation.animations)[animation.currentAnimationId][animation.currentFrame];
		}
		});
}
