#pragma once

#include "lab_m1/tema1/objects/Object_2D.h"

#include "lab_m1/tema1/Constants.h"

using namespace Tema1Constants;

class Enemy : public Object_2D {
public:
	Enemy(const char* name, glm::vec2 position, glm::vec3 color, glm::vec3 secondaryColor, int lives);
	~Enemy();

	void Hit();
	void Update(float deltaTime);
	bool IsDead();

private:
	void InitVertices() override;

private:
	glm::vec3 secondaryColor;
	int lives;

	float radiusEndLenght;
};