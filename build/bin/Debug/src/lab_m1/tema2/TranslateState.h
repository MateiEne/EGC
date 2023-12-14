#pragma once

#include "State.h"
#include "Transform3D.h"

#include "utils/glm_utils.h"

class TranslateXOZState : public State {
public:
	TranslateXOZState(Transform3D* tranform, glm::vec3 targetPosition, float translationSpeed) {
		this->transform = tranform;

		this->targetPosition = targetPosition;
		this->targetPosition.y = 0;
		this->translationSpeed = translationSpeed;

		isTranslating = false;
	}

	void Start() {
		isTranslating = true;

		distance = sqrt(pow((transform->GetPosition().x - targetPosition.x), 2) + pow((transform->GetPosition().z - targetPosition.z), 2));
	}


	void Update(float dt) {
		if (!isTranslating) {
			return;
		}

		float step = dt * translationSpeed;

		if (distance - step <= 0) {
			transform->Translate(glm::vec3(distance * cos(transform->GetRotation().y), 0, distance * sin(transform->GetRotation().y)));

			isTranslating = false;
		}
		else {
			transform->Translate(glm::vec3(step * cos(transform->GetRotation().y), 0, step * sin(transform->GetRotation().y)));

			distance -= step;
		}
	}

	bool HasFinished() {
		return !isTranslating;
	}

private:
	bool vectorEquals(glm::vec3 v1, glm::vec3 v2) {
		return fabs(v1.x - v2.x) < 0.0001 && fabs(v1.y - v2.y) < 0.0001 && fabs(v1.z - v2.z) < 0.0001;
	}

	glm::vec3 GetDirection() {
		return glm::vec3(cos(transform->GetRotation().y), 0, sin(transform->GetRotation().y));
	}

private:
	float distance;

	bool isTranslating;

	Transform3D* transform;

	glm::vec3 targetPosition;
	float translationSpeed;
};