#pragma once

#include "lab_m1/tema2/objects/Tank.h"

#include "lab_m1/tema2/RotateState.h"
#include "lab_m1/tema2/TranslateState.h"
#include "lab_m1/tema2/WaitState.h"

#include <queue>

class DefinedPathTank : public Tank {
public:
	DefinedPathTank(glm::vec3 startPos, glm::vec3 endPos);

	void Update(float dt);

private:
	float RandomFloat(float a, float b);

private:
	queue<State*> states;

	glm::vec3 startPos;
	glm::vec3 endPos;

	glm::vec3 currentPos;
};