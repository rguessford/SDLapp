#include "RenderSystem.h"
#include "comp/textureComponents.h"
#include "comp/actorComponents.h"
#include <iostream>
RenderSystem::RenderSystem(entt::registry& registry, Renderer& renderer) :System(registry), mRenderer(renderer) {}

void RenderSystem::update(float dt) {
	mRegistry.view<drawable, position>().each([&]( auto& drawable, const auto& position) {
		
			//animationsystem has run
			SDL_Rect renderquad = { position.x * 32, position.y * 32,128,128 };
			mRenderer.twoDToIso(&renderquad);
			SDL_RenderCopy(mRenderer, drawable.textureDetails->texture, &drawable.textureDetails->frameMapping->at(drawable.currentFrame), &renderquad);
			
		});
}
