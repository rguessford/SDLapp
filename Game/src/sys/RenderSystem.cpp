#include "RenderSystem.h"
#include "comp/textureComponents.h"
#include "comp/actorComponents.h"
#include <iostream>
#include <util/isomath.h>
RenderSystem::RenderSystem(entt::registry& registry, Renderer& renderer) :System(registry), mRenderer(renderer) {}

void RenderSystem::update(double dt) {
	mRegistry.view<position, camera>().each([&](auto& camera, auto& campos) {
		mRegistry.view<drawable, position>().each([&](auto& drawable, const auto& position) {

			//animationsystem has run
			SDL_Rect renderquad = { position.x , position.y,128,128 };
			twoDToIso(&renderquad);
			renderquad.x -= drawable.textureDetails->foot.x;
			renderquad.y -= drawable.textureDetails->foot.y;
			renderquad.x += campos.xOffset;
			renderquad.y += campos.yOffset;
			SDL_RenderCopy(mRenderer, drawable.textureDetails->texture, &drawable.textureDetails->frameMapping->at(drawable.currentFrame), &renderquad);
		});
	});
}
