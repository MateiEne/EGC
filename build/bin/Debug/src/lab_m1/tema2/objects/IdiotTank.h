#pragma once

#include "Tank.h"
#include "lab_m1/tema2/RotateState.h"

#include <queue>

class IdiotTank : public Tank {
public:
	IdiotTank(glm::vec3 targetPosiition);

	void Update(float dt);

private:
	queue<State*> states;

	glm::vec3 targetPosiition;
};