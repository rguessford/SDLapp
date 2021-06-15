#pragma once
#include <Eigen/Dense>

struct moveCommand {
	Eigen::RowVector2f dir;

	moveCommand(float x, float y) {
		dir(0) = x;
		dir(1) = y;
		dir.normalize();
	}
};