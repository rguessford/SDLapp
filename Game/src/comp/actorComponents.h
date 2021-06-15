#pragma once

struct position {
	//world cooords, not render coords.
	float x, y, z;
};

struct camera {
	float xOffset, yOffset;
	float baseXOffset, baseYOffset;
};

struct keyboardController {};

struct stats {
	float movespeed;
};