#pragma once
 
#include "utils/glm_utils.h"

#include <string>
#include <vector>
#include <map>

namespace CST {
	const float WORLD_SCALE_X = 1000.0;
	const float WORLD_SCALE_Y = 0.1;
	const float WORLD_SCALE_Z = 1000.0;

	const std::string TANK1_ASSETS_FILE_LOCATION = ".\\src\\lab_m1\\tema2\\assets\\Tank1";
	const std::string TANK2_ASSETS_FILE_LOCATION = ".\\src\\lab_m1\\tema2\\assets\\Tank2";
	const std::string TANK3_ASSETS_FILE_LOCATION = ".\\src\\lab_m1\\tema2\\assets\\Tank3";
	const std::string GROUND_ASSETS_FILE_LOCATION = ".\\src\\lab_m1\\tema2\\assets\\ground";
	const std::string BUILDING_ASSETS_FILE_LOCATION = ".\\src\\lab_m1\\tema2\\assets\\buildings";


	const std::string SPHERE_ASSETS_FILE_LOCATION = ".\\src\\lab_m1\\tema2\\assets";


	/*
	"tank1": {
		"base":[0, 0, 0],
		"gun":[1.03784, 0.35, 0],
		"turret":[0, 0.35, 0],
		"rightWheel":[0, -0.21, 0.35],
		"leftWheel":[0, -0.21, -0.35]
	},
	*/
	const glm::vec3 TANK1_BASE_INITIAL_POS = glm::vec3(0, 0, 0);
	const glm::vec3 TANK1_TURRET_INITIAL_POS = glm::vec3(0, 0.35, 0);
	const glm::vec3 TANK1_GUN_INITIAL_POS = glm::vec3(1.03784, 0.35, 0);
	const glm::vec3 TANK1_RIGHT_WHEEL_INITIAL_POS = glm::vec3(0, -0.21, 0.35);
	const glm::vec3 TANK1_LEFT_WHEEL_INITIAL_POS = glm::vec3(0, -0.21, -0.35);


	/*
	"tank2": {
		"base": [0, 0, 0],
		"gun":[0.869467, 0.366997, 0],
		"turret": [0, 0.35024, 0],
		"rightWheel":[0, -0.155503, 0.35],
		"leftWheel":[0, -0.155503, -0.35]
	},
	*/
	const glm::vec3 TANK2_BASE_INITIAL_POS = glm::vec3(0, 0, 0);
	const glm::vec3 TANK2_TURRET_INITIAL_POS = glm::vec3(0, 0.35024, 0);
	const glm::vec3 TANK2_GUN_INITIAL_POS = glm::vec3(0.869467, 0.366997, 0);
	const glm::vec3 TANK2_RIGHT_WHEEL_INITIAL_POS = glm::vec3(0, -0.155503, 0.35);
	const glm::vec3 TANK2_LEFT_WHEEL_INITIAL_POS = glm::vec3(0, -0.155503, -0.35);

	/*
	"tank3": {
		"base":[0, 0, 0],
		"gun":[0.853213, 0.318301, 0],
		"turret":[-0.204477, 0.340029, 0],
		"rightWheel":[0, -0.081699, 0.5],
		"leftWheel":[0, -0.081699, -0.5]
	}
	*/

	const glm::vec3 TANK3_BASE_INITIAL_POS = glm::vec3(0, 0, 0);
	const glm::vec3 TANK3_TURRET_INITIAL_POS = glm::vec3(-0.204477, 0.340029, 0);
	const glm::vec3 TANK3_GUN_INITIAL_POS = glm::vec3(0.853213, 0.318301, 0);
	const glm::vec3 TANK3_RIGHT_WHEEL_INITIAL_POS = glm::vec3(0, -0.081699, 0.5);
	const glm::vec3 TANK3_LEFT_WHEEL_INITIAL_POS = glm::vec3(0, -0.081699, -0.5);

	const std::map<std::string, glm::vec3> COLORS = {
		{"light_green", glm::vec3(187.0f / 256, 237.0f / 256, 201.0f / 256)},
		{"dark_green", glm::vec3(4.0f / 256, 31.0f / 256, 11.0f / 256)},
		{"green", glm::vec3(30.0f / 256, 102.0f / 256, 49.0f / 256)},
		{"black", glm::vec3(7.0f / 256, 8.0f / 256, 7.0f / 256)},
		{"grey", glm::vec3(140.0f / 256, 150.0f / 256, 143.0f / 256)},
		{"light_blue", glm::vec3(66.0f / 256, 95.0f / 256, 199.0f / 256)},
	};

	const float TANK_SPEED = 10;
	const float TANK_ROTATION_SPEED = 90;

	const float MISSILE_SPEED = 15;

	const float COLLISION_OVERLAP_EPS = 0.01;
}