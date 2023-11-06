#pragma once

#include "lab_m1/tema1/objects/Object_2D.h"

class Square : public Object_2D {
public:
	Square(const char* name, glm::vec3 position);
	~Square();

	void InitVertices() override;
};