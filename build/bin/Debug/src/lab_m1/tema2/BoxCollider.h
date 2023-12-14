#pragma once

#include <iostream>

#include "Collider.h"
#include "utils/glm_utils.h"

using namespace std;

class BoxCollider : public Collider {
public:
	virtual float GetLength() = 0; // x
	virtual float GetHeight() = 0; // y
	virtual float GetWidth() = 0; // z

	virtual glm::vec3 GetCenter() = 0;

	ColliderType GetColliderType() {
		return BOX;
	}
};