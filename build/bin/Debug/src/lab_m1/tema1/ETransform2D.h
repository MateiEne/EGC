#pragma once

#include "utils/glm_utils.h"

class Transform2D {
public:
	Transform2D();
	~Transform2D();

	void Translate(glm::vec2 translate);
	void Scale(glm::vec2 scale);
	void Rotate(float radians);

	glm::mat3 GetModelMatrix();

private:
	glm::mat3 modelMatrix;
};