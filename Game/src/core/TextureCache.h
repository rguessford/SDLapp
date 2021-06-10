#pragma once

#include "core/renderer.h"
#include "comp/textureComponents.h"

#include <string>
#include <SDL.h>
#include <SDL_gpu.h>
#include <map>
#include <vector>
#include <memory>

enum class textureNameEnum {
	CUBES, ZOMBIE_0
};

struct TextureDetails {
	TextureDetails() :name(), texture(), frameMapping(), foot() {};
	TextureDetails(textureNameEnum name, GPU_Image* texture, std::shared_ptr <std::vector<GPU_Rect>> frameMapping, SDL_Point foot) :
		name(name), texture(texture), frameMapping(frameMapping), foot(foot) {};
	textureNameEnum name;//textureNameEnum
	GPU_Image* texture;
	std::shared_ptr<std::vector<GPU_Rect>> frameMapping;
	SDL_Point foot;
};

class TextureCache
{
	const std::string assetDir = "assets/";
	std::map<textureNameEnum, std::shared_ptr<TextureDetails>> Cache;
	Renderer& renderer;
	void loadJsonSpritesheetManifest(TextureDetails& textureInfo, std::string filename, Renderer& renderer);
	GPU_Image* loadTexture(const char* path, Renderer& renderer);

public:
	TextureCache(Renderer& renderer) : renderer(renderer) {};
	std::shared_ptr<TextureDetails> getTexture(textureNameEnum);
	void clear(textureNameEnum) {};
	
};

