#pragma once

#include "State.h"
#include "Transform3D.h"

#include "utils/glm_utils.h"

class RotateOYState : public State {
public:
	RotateOYState(Transform3D* tranform, glm::vec3 targetPosition, float rotationSpeed) {
		this->transform = tranform;
		
		this->targetPosition = targetPosition;
		this->targetPosition.y = 0;
		this->rotationSpeed = rotationSpeed;

		isRotating = false;
	}

	void Start() {
		isRotating = true;

		glm::vec3 targetDirection = glm::normalize(targetPosition - transform->GetPosition());
		targetDirection.y = 0;

		glm::vec3 myDirection = GetDirection();

		float angle = acos(glm::dot(targetDirection, myDirection));

		degree = angle * TO_DEGREES;

		if (vectorEquals(T3D::RotateAroundAxis(myDirection, angle, glm::vec3(0, 1, 0)), targetDirection)) {
			sign = 1;
		}
		else {
			sign = -1;
		}
	}


	void Update(float dt) {
		if (!isRotating) {
			return;
		}

		float step = dt * rotationSpeed;

		if (degree - step <= 0) {
			transform->RotateOY(degree * sign);

			isRotating = false;
		}
		else {
			transform->RotateOY(step * sign);

			degree -= step;
		}
	}

	bool HasFinished() {
		return !isRotating;
	}

private:
	bool vectorEquals(glm::vec3 v1, glm::vec3 v2) {
		return fabs(v1.x - v2.x) < 0.0001 && fabs(v1.y - v2.y) < 0.0001 && fabs(v1.z - v2.z) < 0.0001;
	}

	glm::vec3 GetDirection() {
		return glm::vec3(cos(transform->GetRotation().y), 0, sin(transform->GetRotation().y));
	}

private:
	float degree;
	int sign;

	bool isRotating;

	Transform3D* transform;

	glm::vec3 targetPosition;
	float rotationSpeed;
};