#pragma once

#include "utils/glm_utils.h"

class Transform2D {
public:
	Transform2D();
	~Transform2D();

	void SetPosition(glm::vec2 position);
	void SetScale(glm::vec2 scale);
	void SetRotation(float radians);

	void Translate(glm::vec2 translate);
	void Scale(glm::vec2 scale);
	void Rotate(float radians);

	glm::mat3 GetModelMatrix();

private:
	glm::mat3 modelMatrix;
};