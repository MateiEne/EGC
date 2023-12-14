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

	//bool IsInCollision(SphereCollider* other) {
	//	glm::vec3 center = GetCenter();
	//	glm::vec3 otherCenter = other->GetCenter();

	//	float distance = sqrt(pow((otherCenter.x - center.x), 2) + pow((otherCenter.y - center.y), 2) + pow((otherCenter.z - center.z), 2));

	//	return distance < (GetRadius() + other->GetRadius());
	//}

	//bool IsInCollision(BoxCollider* other) {
	//	float buildingMinX = other->GetCenter().x - other->GetLength() / 2;
	//	float buildingMinY = other->GetCenter().y - other->GetHeight() / 2;
	//	float buildingMinZ = other->GetCenter().z - other->GetWidth() / 2;

	//	float buildingMaxX = other->GetCenter().x + other->GetLength() / 2;
	//	float buildingMaxY = other->GetCenter().y + other->GetHeight() / 2;
	//	float buildingMaxZ = other->GetCenter().z + other->GetWidth() / 2;

	//	float x = max(buildingMinX, min(GetCenter().x, buildingMaxX));
	//	float y = max(buildingMinY, min(GetCenter().y, buildingMaxY));
	//	float z = max(buildingMinZ, min(GetCenter().z, buildingMaxZ));

	//	float distance = sqrt(pow((x - GetCenter().x), 2) + pow((y - GetCenter().y), 2) + pow((z - GetCenter().z), 2));

	//	return distance < GetRadius();
	//}
};