#include "RenderSystem.h"
#include "comp/textureComponents.h"
#include "comp/actorComponents.h"
#include <iostream>
#include <util/isomath.h>
RenderSystem::RenderSystem(entt::registry& registry, Renderer& renderer) :System(registry), mRenderer(renderer), fpsCounter(0),fpsTimer(0) {}

void RenderSystem::update(double dt) {
	
	mRegistry.view<position, camera>().each([&](auto& camera, auto& campos) {
		//render tilemap
		mRegistry.view<tileMapRenderer, drawable>().each([&](auto& mapRenderer, const auto& drawable) {
			for (int i = 0; i < 100; i++) {
				for (int j = 0; j < 100; j++) {
					SDL_Rect renderquad = { i * 32 ,j * 32,64,64 };
					twoDToIso(&renderquad);
					renderquad.x += campos.xOffset;
					renderquad.y += campos.yOffset;
					SDL_RenderCopy(mRenderer, drawable.textureDetails->texture, &drawable.textureDetails->frameMapping->at(mapRenderer.tileMap[j][i]), &renderquad);
				}
			}
			});
		//render actors
		mRegistry.sort<drawable>([&](const entt::entity lhs, const entt::entity rhs) {
			return mRegistry.get<position>(lhs).y < mRegistry.get<position>(rhs).y;
		});
		mRegistry.view<drawable, position>().each([&](auto& drawable, const auto& position) {
			if (!drawable.visible) return;
			//animationsystem has run
			SDL_Rect renderquad = { (int)position.x , (int)position.y,128,128 };
			twoDToIso(&renderquad);
			renderquad.x -= drawable.textureDetails->foot.x;
			renderquad.y -= drawable.textureDetails->foot.y;
			renderquad.x += campos.xOffset;
			renderquad.y += campos.yOffset;
			SDL_RenderCopy(mRenderer, drawable.textureDetails->texture, &drawable.textureDetails->frameMapping->at(drawable.currentFrame), &renderquad);
		});
	});
	//we can draw about 3000 zombies before it starts to complain, on my machine
	fpsCounter++;
	fpsTimer += dt;
	if (fpsTimer > 1) { 
		std::cout <<"last 1s fps: " << fpsCounter << "\n";
		fpsCounter = 0;
		fpsTimer = 0;
	}
}
