#pragma once

#include "utils/glm_utils.h"

class Transform2D {
public:
	Transform2D();
	~Transform2D();

	void SetPosition(glm::vec2 position);
	void SetPosition(float x, float y);

	void SetScale(glm::vec2 scale);
	void SetScale(float scaleX, float scaleY);

	void Translate(float translateX, float translateY);
	void Scale(float scaleX, float scaleY);;

	void Translate(glm::vec2 translate);
	void Scale(glm::vec2 scale);
	void Rotate(float radians);

	glm::mat3 GetModelMatrix();

protected:
	glm::mat3 modelMatrix;
	glm::vec2 position;
	glm::vec2 scale;
};