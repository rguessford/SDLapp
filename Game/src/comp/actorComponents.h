#pragma once
#include <glm/glm.hpp>

struct position {
	//world cooords, not render coords.
	glm::vec3 vec3;
	position(float x, float y, float z) : vec3(glm::vec3(x, y, z)) {};
};

struct cameraFocus {
	glm::vec3 vec3;
	cameraFocus(float x, float y, float z) : vec3(glm::vec3(x, y, z)) {};
};

struct keyboardController {};

struct stats {
	float movespeed;
};