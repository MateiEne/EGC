#pragma once

#include "lab_m1/tema1/objects/Object_2D.h"

class Enemy : public Object_2D {
public:
	Enemy(const char* name, glm::vec2 position, glm::vec3 color, glm::vec3 secondaryColor);
	~Enemy();

private:
	void InitVertices() override;

private:
	glm::vec3 secondaryColor;
};