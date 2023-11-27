#include "utils/glm_utils.h"

namespace CST {
	const glm::vec3 TANK_BASE_INITIAL_POS = glm::vec3(0, 0.2, 0);
	const glm::vec3 TANK_TURRET_INITIAL_POS = glm::vec3(0, 0.55, 0);
	const glm::vec3 TANK_GUN_INITIAL_POS = glm::vec3(1.0268, 0.55, 0);
	const glm::vec3 TANK_RIGHT_WHEEL_INITIAL_POS = glm::vec3(0, -0.01, 0.35);
	const glm::vec3 TANK_LEFT_WHEEL_INITIAL_POS = glm::vec3(0, -0.01, -0.35);

	const float TANK_SPEED = 2;
	const float TANK_ROTATION_SPEED = 90;
}