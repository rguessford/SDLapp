#include "TextureCache.h"
#include "core/Renderer.h"

#include <fstream>
#include <rapidjson/document.h>
#include <string>
#include <SDL_image.h>

std::shared_ptr<TextureDetails> TextureCache::getTexture(textureNameEnum textureEnum)
{
	std::map<textureNameEnum, std::shared_ptr<TextureDetails>>::iterator it;
	auto textureInfo = std::make_shared<TextureDetails>();
	SDL_Point emptyPoint = { 0,0 };
	switch (textureEnum) {
	case textureNameEnum::CUBES:
		it = Cache.find(textureNameEnum::CUBES);
		if (it == Cache.end()) { //not found
			textureInfo = std::make_shared<TextureDetails>(textureNameEnum::CUBES, (SDL_Texture*)NULL, std::make_shared<std::vector<SDL_Rect>>(), emptyPoint);
			std::string json = assetDir + "cubes.json";
			loadJsonSpritesheetManifest((*textureInfo), json, renderer);
			Cache.insert(std::pair<textureNameEnum, std::shared_ptr<TextureDetails>>(textureNameEnum::CUBES, textureInfo));
		}
		else {
			textureInfo = it->second;
		}
		break;
	case textureNameEnum::ZOMBIE_0:
		it = Cache.find(textureNameEnum::ZOMBIE_0);
		if (it == Cache.end()) { //not found
			textureInfo = std::make_shared<TextureDetails>(textureNameEnum::CUBES, (SDL_Texture*)NULL, std::make_shared<std::vector<SDL_Rect>>(), emptyPoint);
			std::string json = assetDir + "zombie_0.json";
			loadJsonSpritesheetManifest((*textureInfo), json, renderer);
			Cache.insert(std::pair<textureNameEnum, std::shared_ptr<TextureDetails>>(textureNameEnum::ZOMBIE_0, textureInfo));
		}
		else {
			textureInfo = it->second;
		}
		break;
	}

	return textureInfo;
}

void TextureCache::loadJsonSpritesheetManifest(TextureDetails& textureInfo, std::string filename, Renderer& renderer) {
	std::ifstream ifs(filename);
	std::string content((std::istreambuf_iterator<char>(ifs)),
		(std::istreambuf_iterator<char>()));
	rapidjson::Document d;
	d.Parse(content.c_str());

	const rapidjson::Value& meta = d["meta"];
	std::string spritesheetImagePath = assetDir + meta["image"].GetString();
	const rapidjson::Value& frames = d["frames"];
	
	if (meta.HasMember("origin-foot-offset")) {
		const rapidjson::Value& foot = meta["origin-foot-offset"];
		textureInfo.foot.x = foot["x"].GetInt();
		textureInfo.foot.y = foot["y"].GetInt();
	}

	assert(frames.IsArray());
	const rapidjson::GenericArray frameArray = frames.GetArray();
	//create an array of sdl rects specifying all the sprites in the texture
	int size = frameArray.Size();

	textureInfo.frameMapping->reserve(size);

	for (int i = 0; i < size; i++) {
		const rapidjson::Value& rect = frameArray[i]["frame"];
		const SDL_Rect frame{ rect["x"].GetInt(),rect["y"].GetInt(),rect["w"].GetInt(),rect["h"].GetInt() };
		textureInfo.frameMapping->push_back(frame);
	}

	textureInfo.texture = loadTexture(spritesheetImagePath.c_str(), renderer);
}

SDL_Texture* TextureCache::loadTexture(const char* path, Renderer& renderer)
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path);
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}
