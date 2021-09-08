#pragma once

#include "comp/textureComponents.h"

#include <string>
#include <SDL.h>
#include <map>
#include <vector>
#include <memory>

enum class GLtextureNameEnum {
	CUBES, ZOMBIE_0, BRICK_02
};

struct GLTextureDetails {
	GLTextureDetails() :name(), texture(), frameMapping(), foot() {};
	GLTextureDetails(GLtextureNameEnum name, unsigned int texture, std::shared_ptr <std::vector<SDL_Rect>> frameMapping, SDL_Point foot) :
		name(name), texture(texture), frameMapping(frameMapping), foot(foot) {};
	GLtextureNameEnum name;//textureNameEnum
	unsigned int texture;
	std::shared_ptr<std::vector<SDL_Rect>> frameMapping;
	SDL_Point foot;
};

class GLTextureCache
{
	const std::string assetDir = "assets/";
	std::map<GLtextureNameEnum, std::shared_ptr<GLTextureDetails>> Cache;
	unsigned int loadTexture(const char* path);

public:
	GLTextureCache() {};
	std::shared_ptr<GLTextureDetails> getTexture(GLtextureNameEnum);
	void clear(GLtextureNameEnum) {};
	void init();
};