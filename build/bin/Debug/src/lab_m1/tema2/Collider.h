#pragma once

#include <iostream>

using namespace std;

enum ColliderType {
	SPHERE,
	BOX
};

class Collider {
public:
	virtual ColliderType GetColliderType() = 0;

	bool IsInCollision(Collider* other);

	virtual void TakeDamage(Collider* collider) = 0;
};