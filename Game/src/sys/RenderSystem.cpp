#include "RenderSystem.h"
#include "comp/textureComponents.h"
#include "comp/actorComponents.h"
RenderSystem::RenderSystem(entt::registry& registry, Renderer& renderer) :System(registry, renderer) {}

void RenderSystem::update(float dt) {
	mRegistry.view<drawable, position>().each([&]( auto& drawable, const auto& position) {
			SDL_Rect renderquad = { position.x * 32, position.y * 32,128,128 };
			mRenderer.twoDToIso(&renderquad);
			SDL_RenderCopy(mRenderer, drawable.texutreDetails->texture, &drawable.texutreDetails->frameMapping->at(drawable.currentFrame), &renderquad);
			drawable.currentFrame = (drawable.currentFrame + 1) % 288;
		});
}
