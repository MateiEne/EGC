#pragma once

#include "utils/glm_utils.h"

#include <string>

namespace CST {
	const std::string TANK_ASSETS_FILE_LOCATION = "C:\\gfx framework\\gfx-framework-master\\gfx-framework-master\\src\\lab_m1\\tema2\\assets\\Tank1";

	const glm::vec3 TANK_BASE_INITIAL_POS = glm::vec3(0, 0.2, 0);
	const glm::vec3 TANK_TURRET_INITIAL_POS = glm::vec3(0, 0.55, 0);
	const glm::vec3 TANK_GUN_INITIAL_POS = glm::vec3(1.0268, 0.55, 0);
	const glm::vec3 TANK_RIGHT_WHEEL_INITIAL_POS = glm::vec3(0, -0.01, 0.35);
	const glm::vec3 TANK_LEFT_WHEEL_INITIAL_POS = glm::vec3(0, -0.01, -0.35);

	const float TANK_SPEED = 10;
	const float TANK_ROTATION_SPEED = 90;

	const float MISSILE_SPEED = 15;
}