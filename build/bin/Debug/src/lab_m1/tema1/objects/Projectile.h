#pragma once

#include "lab_m1/tema1/objects/Object_2D.h"

class Projectile : public Object_2D {
public:
	Projectile(const char* name, glm::vec3 position);
	~Projectile();

	void Init() override;
};