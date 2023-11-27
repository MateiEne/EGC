#pragma once

#include <iostream>
#include "utils/glm_utils.h"


namespace T3D
{
	// Translate matrix
	inline glm::mat4 Translate(float translateX, float translateY, float translateZ)
	{
		// TODO(student): Implement the translation matrix
		return glm::transpose(
			glm::mat4(
				1, 0, 0, translateX,
				0, 1, 0, translateY,
				0, 0, 1, translateZ,
				0, 0, 0, 1
			)
		);

	}

	// Scale matrix
	inline glm::mat4 Scale(float scaleX, float scaleY, float scaleZ)
	{
		// TODO(student): Implement the scaling matrix
		return glm::transpose(
			glm::mat4(
				scaleX, 0, 0, 0,
				0, scaleY, 0, 0,
				0, 0, scaleZ, 0,
				0, 0, 0, 1
			)
		);

	}

	// Rotate matrix relative to the OZ axis
	inline glm::mat4 RotateOZ(float degrees)
	{
		// TODO(student): Implement the rotation matrix
		return glm::transpose(
			glm::mat4(
				cos(degrees), -sin(degrees), 0, 0,
				sin(degrees), cos(degrees), 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1
			)
		);

	}

	// Rotate matrix relative to the OY axis
	inline glm::mat4 RotateOY(float degrees)
	{
		// TODO(student): Implement the rotation matrix
		return glm::transpose(
			glm::mat4(
				cos(degrees), 0, -sin(degrees), 0,
				0, 1, 0, 0,
				sin(degrees), 0, cos(degrees), 0,
				0, 0, 0, 1
			)
		);

	}

	// Rotate matrix relative to the OX axis
	inline glm::mat4 RotateOX(float degrees)
	{
		// TODO(student): Implement the rotation matrix
		return glm::transpose(
			glm::mat4(
				1, 0, 0, 0,
				0, cos(degrees), -sin(degrees), 0,
				0, sin(degrees), cos(degrees), 0,
				0, 0, 0, 1
			)
		);

	}

	inline float degreesToRadians(float degrees) {
		return degrees * 3.14 / 180.0;
	}
}   // namespace T3D

class Transform3D {
public:
	Transform3D();
	~Transform3D();

	void SetPosition(glm::vec3 position);
	void SetPosition(float x, float y, float z);

	void SetScale(glm::vec3 scale);
	void SetScale(float scaleX, float scaleY, float scaleZ);

	void Translate(glm::vec3 translate);
	void Translate(float translateX, float translateY, float translateZ);
	
	void Scale(glm::vec3 scale);
	void Scale(float scaleX, float scaleY, float scaleZ);

	void RotateOX(float degrees);
	void RotateOY(float degrees);
	void RotateOZ(float degrees);

	glm::mat4 GetModelMatrix();

protected:
	glm::vec3 position;
	glm::vec3 scale;
	float degreesOX;
	float degreesOY;
	float degreesOZ;
};
