#pragma once

#include "BoxCollider.h"
#include "Collider.h"
#include "utils/glm_utils.h"

#include <iostream>

using namespace std;

class SphereCollider : public Collider {
public:
	virtual glm::vec3 GetCenter() = 0;
	virtual float GetRadius() = 0;

	ColliderType GetColliderType() {
		return SPHERE;
	}
};