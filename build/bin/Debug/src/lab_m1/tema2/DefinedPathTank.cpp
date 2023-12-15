#include "DefinedPathTank.h"

DefinedPathTank::DefinedPathTank(glm::vec3 startPos, glm::vec3 endPos) {
	this->startPos = startPos;
	this->endPos = endPos;

	currentPos = startPos;
}

void DefinedPathTank::Update(float dt) {
	if (hp <= 0) {
		return;
	}

	Tank::Update(dt);

	if (states.empty()) {
		states.push(new WaitState(RandomFloat(CST::MIN_WAIT_TIME, CST::MAX_WAIT_TIME)));

		if (currentPos == startPos) {
			states.push(new RotateOYState(this, endPos, 50));
			states.push(new TranslateXOZState(this, endPos, 10));
		
			currentPos = endPos;
		}
		else {
			states.push(new RotateOYState(this, startPos, 50));
			states.push(new TranslateXOZState(this, startPos, 10));

			currentPos = startPos;
		}
	}

	states.front()->Update(dt);

	if (states.front()->HasFinished()) {
		states.pop();

		if (!states.empty()) {
			states.front()->Start();
		}
	}
}

float DefinedPathTank::RandomFloat(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;

	return a + r;
}