#pragma once

#include <map>
#include <vector>
#include <memory>

enum class animationEnum {
	ZOMBIE_0
};

class AnimationRepository
{
	std::map<animationEnum, std::shared_ptr<std::vector<std::vector<int>>>> Cache;
public:
	std::shared_ptr<std::vector<std::vector<int>>> getAnimation(animationEnum);
	void clear(animationEnum) {};
};
