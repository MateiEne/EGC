#include "IdiotTank.h"

IdiotTank::IdiotTank(glm::vec3 targetPosiition) : Tank() {
	this->targetPosiition = targetPosiition;
}

void IdiotTank::Update(float dt) {
	if (hp <= 0) {
		return;
	}

	Tank::Update(dt);


	if (states.empty()) {
		cout << "ASdasdasdasdds" << endl;
		states.push(new RotateOYState(this, targetPosiition, 100));
		states.front()->Start();
	}

	states.front()->Update(dt);
}
