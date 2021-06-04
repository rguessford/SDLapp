#include "entityFactories.h"
#include "comp/tileMapComponents.h"
#include "util/sdl_load_texture.h"

#include <rapidjson/document.h>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

//returns the path to the spritesheet, to be used with loadTexture
std::string loadJsonSpritesheetManifest(std::vector<SDL_Rect>& frameVector, std::string filename) {
	std::ifstream ifs(filename);
	std::string content((std::istreambuf_iterator<char>(ifs)),
		(std::istreambuf_iterator<char>()));
	rapidjson::Document d;
	d.Parse(content.c_str());

	const rapidjson::Value& meta = d["meta"];
	std::string spritesheetImagePath = meta["imagepath"].GetString();
	const rapidjson::Value& frames = d["frames"];

	assert(frames.IsArray());
	const rapidjson::GenericArray frameArray = frames.GetArray();
	//create an array of sdl rects specifying all the sprites in the texture
	int size = frameArray.Size();

	frameVector.reserve(size);

	for (int i = 0; i < size; i++) {
		const rapidjson::Value& rect = frameArray[i]["frame"];
		const SDL_Rect frame{ rect["x"].GetInt(),rect["y"].GetInt(),rect["w"].GetInt(),rect["h"].GetInt() };
		frameVector.push_back(frame);
	}

	return spritesheetImagePath;
}

//creates an entity to represent and draw a tilemap
entt::entity makeTilemap(entt::registry& reg, Renderer& renderer)
{
	//json is used as the spritesheet manifest
	std::vector<SDL_Rect> frameMapping;
	std::string spritesheetImagePath = loadJsonSpritesheetManifest(frameMapping, "assets/cubes.json");
	auto tilemapEntity = reg.create();
	reg.emplace<spriteSheet>(tilemapEntity, loadTexture(spritesheetImagePath.c_str(), renderer), frameMapping, (int)frameMapping.size());
	reg.emplace<tileMapRenderer>(tilemapEntity, 100, 100);

	return tilemapEntity;
}
