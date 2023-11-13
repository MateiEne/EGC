#pragma once

#include "glm/glm.hpp"

#include <vector>

namespace Tema1Constants {
	const int CAMERA_ORTHO_WIDTH = 60;
	const int CAMERA_ORTHO_HEIGHT = 30;

	const glm::vec3 GREEN_COLOR = glm::vec3(34.0f / 256, 139.0f / 256, 34.0f / 256);
	const glm::vec3 ORANGE_COLOR = glm::vec3(255 / 255.f, 128 / 256.f, 0);
	const glm::vec3 BLUE_COLOR = glm::vec3(0.f, 0.f, 204 / 256.f);
	const glm::vec3 YELLOW_COLOR = glm::vec3(204 / 256.f, 204 / 256.f, 0.f);
	const glm::vec3 PURPLE_COLOR = glm::vec3(102 / 256.f, 0.f, 204 / 256.f);
	const glm::vec3 GREY_COLOR = glm::vec3(192 / 256.f, 192 / 256.f, 192 / 256.f);
	const glm::vec3 RED_COLOR = glm::vec3(1, 0, 0);
	const glm::vec3 WHITE_COLOR = glm::vec3(1, 1, 1);
	const glm::vec3 GOLD_COLOR = glm::vec3(153 / 256.f, 153 / 256.f, 0);

	const glm::vec2 TURRET_SCALE = glm::vec2(1.5f, 1.8f);
	const glm::vec2 RANDOM_MONEY_SCALE = glm::vec2(2.f, 2.f);
	const glm::vec2 TOTAL_MONEY_SCALE = glm::vec2(1.1f, 1.1f);

	/*glm::vec3 CHARACTERS_COLORS[] = { ORANGE_COLOR, BLUE_COLOR, YELLOW_COLOR, PURPLE_COLOR };
	glm::vec3 CHARACTERS_SECONDARY_COLORS[] = { GREEN_COLOR, GREY_COLOR, WHITE_COLOR };*/

	const int SPAWN_RANDOM_MONEY_INTERVAL_HIGH = 7;
	const int SPAWN_RANDOM_MONEY_INTERVAL_LOW = 3;

	const int SPAWN_RANDOM_ENEMIES_INTERVAL_HIGH = 7;
	const int SPAWN_RANDOM_ENEMIES_INTERVAL_LOW = 3;

	const float TOTAL_MONEY_START_X = 42.f;
	const float TOTAL_MONEY_START_Y = 24.3f;
}