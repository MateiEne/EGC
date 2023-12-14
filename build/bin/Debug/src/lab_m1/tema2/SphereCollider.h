#pragma once

#include "core/engine.h"

class SphereCollider {
public:
	virtual glm::vec3 GetCenter() = 0;
	virtual float GetRadius() = 0;

	bool IsInCollision(SphereCollider* other) {
		glm::vec3 center = GetCenter();
		glm::vec3 otherCenter = other->GetCenter();

		float distance = sqrt(pow((otherCenter.x - center.x), 2) + pow((otherCenter.y - center.y), 2) + pow((otherCenter.z - center.z), 2));

		return distance < (GetRadius() + other->GetRadius());
	}
};