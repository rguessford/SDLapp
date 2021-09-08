#include "GLTextureCache.h"

#include <glbinding/gl/gl.h>
#pragma warning(once: 4251)
#include <glbinding/Binding.h>
#pragma warning(default: 4251)

#include <iostream>

#define STBI_ONLY_PNG
#define STB_IMAGE_IMPLEMENTATION
#include "core/stb_image.h"
using namespace gl;

unsigned int GLTextureCache::loadTexture(const char* path)
{
	int width, height, nrChannels;
	unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);

	unsigned int texture;
	glGenTextures(1, &texture);

	glBindTexture(GL_TEXTURE_2D, texture);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	return texture;
}

std::shared_ptr<GLTextureDetails> GLTextureCache::getTexture(GLtextureNameEnum textureEnum)
{
	std::map<GLtextureNameEnum, std::shared_ptr<GLTextureDetails>>::iterator it;
	auto textureInfo = std::make_shared<GLTextureDetails>();
	SDL_Point emptyPoint = { 0,0 };
	switch (textureEnum) {
	case GLtextureNameEnum::CUBES:
		it = Cache.find(GLtextureNameEnum::CUBES);
		if (it == Cache.end()) { //not found
			std::string path = assetDir + "cubes.png";
			textureInfo = std::make_shared<GLTextureDetails>(GLtextureNameEnum::CUBES, loadTexture(path.c_str()), std::make_shared<std::vector<SDL_Rect>>(), emptyPoint);
			Cache.insert(std::pair<GLtextureNameEnum, std::shared_ptr<GLTextureDetails>>(GLtextureNameEnum::CUBES, textureInfo));
		}
		else {
			textureInfo = it->second;
		}
		break;
	case GLtextureNameEnum::ZOMBIE_0:
		it = Cache.find(GLtextureNameEnum::ZOMBIE_0);
		if (it == Cache.end()) { //not found
			std::string path = assetDir + "zombie_0.png";
			textureInfo = std::make_shared<GLTextureDetails>(GLtextureNameEnum::ZOMBIE_0, loadTexture(path.c_str()) , std::make_shared<std::vector<SDL_Rect>>(), emptyPoint);
			Cache.insert(std::pair<GLtextureNameEnum, std::shared_ptr<GLTextureDetails>>(GLtextureNameEnum::ZOMBIE_0, textureInfo));
		}
		else {
			textureInfo = it->second;
		}
		break;
	case GLtextureNameEnum::BRICK_02:
		it = Cache.find(GLtextureNameEnum::BRICK_02);
		if (it == Cache.end()) { //not found
			std::string path = assetDir + "Brick_02.png";
			textureInfo = std::make_shared<GLTextureDetails>(GLtextureNameEnum::BRICK_02, loadTexture(path.c_str()), std::make_shared<std::vector<SDL_Rect>>(), emptyPoint);
			Cache.insert(std::pair<GLtextureNameEnum, std::shared_ptr<GLTextureDetails>>(GLtextureNameEnum::BRICK_02, textureInfo));
		}
		else {
			textureInfo = it->second;
		}
		break;
	}

	return textureInfo;
}

void GLTextureCache::init()
{
	stbi_set_flip_vertically_on_load(true);
}
