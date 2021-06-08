#include "sys/TileManager.h"
#include "comp/textureComponents.h"
#include "comp/actorComponents.h"
#include <SDL.h>
#include <util/isomath.h>

void TileManager::update(double dt) {
	mRegistry.view<position, camera>().each([&](auto& camera, auto& campos ) {
		mRegistry.view<tileMapRenderer, drawable>().each([&](auto& mapRenderer, const auto& drawable) {
			for (int i = 0; i < 100; i++) {
				for (int j = 0; j < 100; j++) {
					mapRenderer.tileMap[j][i] = (i + j) % 34;
					SDL_Rect renderquad = { i * 32 ,j * 32,64,64 };
					twoDToIso(&renderquad);
					renderquad.x += campos.xOffset;
					renderquad.y += campos.yOffset;
					SDL_RenderCopy(mRenderer, drawable.textureDetails->texture, &drawable.textureDetails->frameMapping->at(mapRenderer.tileMap[j][i]), &renderquad);
				}
			}
		});
	});
}

TileManager::TileManager(entt::registry& registry, Renderer& renderer) :System(registry), mRenderer(renderer) {}
