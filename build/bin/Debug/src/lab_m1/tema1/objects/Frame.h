#pragma once

#include "lab_m1/tema1/objects/Object_2D.h"

class Frame : public Object_2D {
public:
	Frame(const char* name, glm::vec2 position, glm::vec3 color);
	~Frame();

	float GetWidth();
	float GetHeight();

private:
	void InitVertices() override;

private:
	float width;
	float height;
};