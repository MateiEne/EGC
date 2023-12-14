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

		states.push(new WaitState(3));

		states.push(new TranslateXOZState(this, targetPosiition, 10));


	}

	states.front()->Update(dt);

	if (states.front()->HasFinished()) {
		states.pop();

		states.front()->Start();
	}
}
