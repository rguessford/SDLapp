#pragma once

struct position {
	//world cooords, not render coords.
	float x, y, z;
};

struct camera {
	float xOffset, yOffset;
};

struct keyboardController {};