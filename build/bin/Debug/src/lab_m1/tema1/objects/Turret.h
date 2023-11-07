#pragma once

#include "lab_m1/tema1/objects/Object_2D.h"

class Turret : public Object_2D {
public:
	Turret(const char* name, glm::vec2 position, glm::vec3 color, int cost);
	~Turret();

private:
	void InitVertices() override;
	int GetCost();

	int cost;
};