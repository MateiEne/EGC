#include "IdiotTank.h"

IdiotTank::IdiotTank(glm::vec3 lowerBound, glm::vec3 upperBound) : Tank() {
	this->lowerBound = lowerBound;
	this->upperBound = upperBound;


}

void IdiotTank::Update(float dt) {
	if (hp <= 0) {
		return;
	}

	Tank::Update(dt);


	if (states.empty()) {
		AddNewStates();

		states.front()->Start();
	}

	states.front()->Update(dt);

	if (states.front()->HasFinished()) {
		states.pop();

		if (!states.empty()) {
			states.front()->Start();
		}
	}
}

void IdiotTank::AddNewStates() {
	if (rand() % CST::WAIT_STATE_PROBABILITY == 0) {
		states.push(new WaitState(RandomFloat(CST::MIN_WAIT_TIME, CST::MAX_WAIT_TIME)));
	}

	glm::vec3 targetPos = GetNextTargetPoint();
	states.push(new RotateOYState(this, targetPos, 50));
	states.push(new TranslateXOZState(this, targetPos, 10));
}

glm::vec3 IdiotTank::GetNextTargetPoint() {

	return glm::vec3(RandomFloat(lowerBound.x, upperBound.x), RandomFloat(lowerBound.y, upperBound.y), RandomFloat(lowerBound.z, upperBound.z));
}

float IdiotTank::RandomFloat(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;

	return a + r;
}