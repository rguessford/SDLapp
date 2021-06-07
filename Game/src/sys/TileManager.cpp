#include "sys/TileManager.h"
#include "comp/textureComponents.h"
#include <SDL.h>

void TileManager::update(float dt) {
	mRegistry.view<tileMapRenderer, drawable>().each([&](auto& mapRenderer, const auto& drawable) {
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++) {
				mapRenderer.tileMap[j][i] = (i + j) % 34;
				SDL_Rect renderquad = { i * 32 + 800,j * 32,64,64 };
				mRenderer.twoDToIso(&renderquad);
				SDL_RenderCopy(mRenderer, drawable.textureDetails->texture, &drawable.textureDetails->frameMapping->at(mapRenderer.tileMap[j][i]), &renderquad);
			}
		}
	});
}

TileManager::TileManager(entt::registry& registry, Renderer& renderer) :System(registry), mRenderer(renderer) {}
