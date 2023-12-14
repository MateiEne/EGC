#pragma once

#include "State.h"
#include "Transform3D.h"

#include "utils/glm_utils.h"

class WaitState : public State {
public:
	WaitState(float seconds) {
		this->seconds = seconds;

		isWaiting = false;
	}

	void Start() {
		isWaiting = true;
	}


	void Update(float dt) {
		if (!isWaiting) {
			return;
		}

		if (seconds - dt <= 0) {
			isWaiting = false;
		}
		else {
			seconds -= dt;
		}
	}

	bool HasFinished() {
		return !isWaiting;
	}

private:
	float seconds;

	bool isWaiting;
};