#pragma once

#include "lab_m1/tema1/objects/Object_2D.h"

class Square : public Object_2D {
public:
	Square(const char* name, glm::vec2 position, glm::vec3 color);
	~Square();

	void InitVertices() override;
};