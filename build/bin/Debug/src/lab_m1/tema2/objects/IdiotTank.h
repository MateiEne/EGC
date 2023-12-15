#pragma once

#include "Tank.h"
#include "lab_m1/tema2/RotateState.h"
#include "lab_m1/tema2/TranslateState.h"
#include "lab_m1/tema2/WaitState.h"

#include <queue>

class IdiotTank : public Tank {
public:
	IdiotTank(glm::vec3 lowerBound, glm::vec3 upperBound);

	void Update(float dt);

private:
	float RandomFloat(float a, float b);
	void AddNewStates();
	glm::vec3 GetNextTargetPoint();

	queue<State*> states;

	glm::vec3 lowerBound; 
	glm::vec3 upperBound;
};