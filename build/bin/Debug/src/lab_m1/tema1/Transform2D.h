#pragma once

#include "utils/glm_utils.h"

namespace T2D
{
	// Translate matrix
	inline glm::mat3 Translate(float translateX, float translateY)
	{
		// TODO(student): Implement the translation matrix
		return glm::transpose(
			glm::mat3(1, 0, translateX,
				0, 1, translateY,
				0, 0, 1)
		);

	}

	// Scale matrix
	inline glm::mat3 Scale(float scaleX, float scaleY)
	{
		// TODO(student): Implement the scaling matrix
		return glm::transpose(
			glm::mat3(scaleX, 0, 0,
				0, scaleY, 0,
				0, 0, 1)
		);

	}

	// Rotate matrix
	inline glm::mat3 Rotate(float radians)
	{
		// TODO(student): Implement the rotation matrix
		return glm::transpose(
			glm::mat3(cos(radians), -sin(radians), 0,
				sin(radians), cos(radians), 0,
				0, 0, 1)
		);

	}
}   // namespace transform2D

class Transform2D {
public:
	Transform2D();
	~Transform2D();

	void SetPosition(glm::vec2 position);
	void SetPosition(float x, float y);

	void SetScale(glm::vec2 scale);
	void SetScale(float scaleX, float scaleY);

	void Translate(float translateX, float translateY);
	void Scale(float scaleX, float scaleY);

	void Translate(glm::vec2 translate);
	void Scale(glm::vec2 scale);
	void Rotate(float radians);

	glm::mat3 GetModelMatrix();

protected:
	glm::vec2 position;
	glm::vec2 scale;
	float radians;
};