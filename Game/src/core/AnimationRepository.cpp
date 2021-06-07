#include "AnimationRepository.h"

#include <map>
#include <vector>
#include <memory>

std::shared_ptr<std::vector<std::vector<int>>> AnimationRepository::getAnimation(animationEnum animation)
{
	std::map<animationEnum, std::shared_ptr<std::vector<std::vector<int>>>>::iterator it;
	auto animations = std::make_shared<std::vector<std::vector<int>>> ();
	switch (animation) {
	case (animationEnum::ZOMBIE_0):
		it = Cache.find(animationEnum::ZOMBIE_0);
		if (it == Cache.end()) { //not found
			animations = std::make_shared<std::vector<std::vector<int>>>(
				std::vector<std::vector<int>>
				{ 
					{0,1,2,3},//idle
					{4,5,6,7,8,9,10,11},//walk
					{12,13,14,15},//attack1
					{16,17,18,19},//attack2
					{20,21},//block
					{22,23,24,25,26,27},//die1
					{28,29,30,31,32,33,34,35}//die2
				}
			);
			Cache.insert(std::pair<animationEnum, std::shared_ptr<std::vector<std::vector<int>>>>(animationEnum::ZOMBIE_0, animations));
		}
		else {
			animations = it->second;
		}
		break;
	}
	return animations;
}
