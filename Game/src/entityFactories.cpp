#include "entityFactories.h"
#include "Components.h"
#include "util/sdl_load_texture.h"

#include <rapidjson/document.h>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>


//creates an entity to represent and draw a tilemap
entt::entity makeDefaultTilemap(entt::registry& reg, Renderer* renderer)
{
	//json is used as the spritesheet manifest
	std::ifstream ifs("assets/cubes.json");
	std::string content((std::istreambuf_iterator<char>(ifs)),
		(std::istreambuf_iterator<char>()));
	rapidjson::Document d;
	d.Parse(content.c_str());
	
	const rapidjson::Value& meta = d["meta"];
	const char* spritesheetImagePath = meta["imagepath"].GetString();

	const rapidjson::Value& frames = d["frames"];

	
	assert(frames.IsArray());
	const rapidjson::GenericArray frameArray = frames.GetArray();
	//create an array of sdl rects specifying all the sprites in the texture
	int size = frameArray.Size();
	std::vector<SDL_Rect> frameMapping;
	frameMapping.reserve(size);

	for (int i = 0; i < size; i++){
		const rapidjson::Value& rect = frameArray[i]["frame"];
		const SDL_Rect frame{ rect["x"].GetInt(),rect["y"].GetInt(),rect["w"].GetInt(),rect["h"].GetInt() };
		frameMapping.push_back(frame);
	}
	
	auto tilemapEntity = reg.create();
	reg.emplace<spriteSheet>(tilemapEntity, loadTexture(spritesheetImagePath, renderer), frameMapping, (int)frameArray.Size());
	reg.emplace<tileMapRenderer>(tilemapEntity, 100, 100);

	return tilemapEntity;
}
