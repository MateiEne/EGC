#pragma once

#include "utils/glm_utils.h"

#include <string>
#include <vector>
#include <map>

namespace CST {
	const std::string TANK_ASSETS_FILE_LOCATION = "C:\\gfx framework\\gfx-framework-master\\gfx-framework-master\\src\\lab_m1\\tema2\\assets\\Tank1";
	const std::string GROUND_ASSETS_FILE_LOCATION = "C:\\gfx framework\\gfx-framework-master\\gfx-framework-master\\src\\lab_m1\\tema2\\assets\\ground";

	const glm::vec3 TANK_BASE_INITIAL_POS = glm::vec3(0, 0.2, 0);
	const glm::vec3 TANK_TURRET_INITIAL_POS = glm::vec3(0, 0.55, 0);
	const glm::vec3 TANK_GUN_INITIAL_POS = glm::vec3(1.0268, 0.55, 0);
	const glm::vec3 TANK_RIGHT_WHEEL_INITIAL_POS = glm::vec3(0, -0.01, 0.35);
	const glm::vec3 TANK_LEFT_WHEEL_INITIAL_POS = glm::vec3(0, -0.01, -0.35);

	const std::map<std::string, glm::vec3> COLORS = {
		{"light_green", glm::vec3(187.0f / 256, 237.0f / 256, 201.0f / 256)},
		{"dark_green", glm::vec3(4.0f / 256, 31.0f / 256, 11.0f / 256)},
		{"green", glm::vec3(30.0f / 256, 102.0f / 256, 49.0f / 256)},
		{"black", glm::vec3(7.0f / 256, 8.0f / 256, 7.0f / 256)},
		{"grey", glm::vec3(140.0f / 256, 150.0f / 256, 143.0f / 256)},
	};

	const float TANK_SPEED = 10;
	const float TANK_ROTATION_SPEED = 90;

	const float MISSILE_SPEED = 15;
}