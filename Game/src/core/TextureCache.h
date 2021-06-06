#pragma once

#include "core/renderer.h"
#include "comp/textureComponents.h"

#include <string>
#include <SDL.h>
#include <map>
#include <vector>
#include <memory>

enum class textureNameEnum {
	CUBES, ZOMBIE_0
};

struct TextureDetails {
	TextureDetails() :name(), texture(), frameMapping(), foot() {};
	TextureDetails(textureNameEnum name, SDL_Texture* texture, std::shared_ptr <std::vector<SDL_Rect>> frameMapping, SDL_Point foot) :
		name(name), texture(texture), frameMapping(frameMapping), foot(foot) {};
	textureNameEnum name;//textureNameEnum
	SDL_Texture* texture;
	std::shared_ptr<std::vector<SDL_Rect>> frameMapping;
	SDL_Point foot;
};

class TextureCache
{
	const std::string assetDir = "assets/";
	std::map<textureNameEnum, std::shared_ptr<TextureDetails>> Cache;
	Renderer& renderer;
	void loadJsonSpritesheetManifest(TextureDetails& textureInfo, std::string filename, Renderer& renderer);
	SDL_Texture* loadTexture(const char* path, Renderer& renderer);

public:
	TextureCache(Renderer& renderer) : renderer(renderer) {};
	std::shared_ptr<TextureDetails> getTexture(textureNameEnum);
	void clear(textureNameEnum) {};
	
};

