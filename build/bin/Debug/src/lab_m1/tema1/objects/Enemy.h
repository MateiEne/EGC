#pragma once

#include "lab_m1/tema1/objects/Object_2D.h"

class Enemy : public Object_2D {
public:
	Enemy(const char* name, glm::vec3 position);
	~Enemy();

	void Init() override;
};