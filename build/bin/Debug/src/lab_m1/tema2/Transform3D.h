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

	inline glm::vec3 RotateAroundAxis(glm::vec3 vector, float radians, glm::vec3 axis, glm::vec3 center = glm::vec3(0)) {
		// Translate the vector and center of rotation
		glm::vec3 translatedVector = vector - center;

		// Normalize the axis vector
		axis = glm::normalize(axis);

		// The rotation matrix for rotating a vector around an arbitrary axis is derived from Rodrigues' rotation
		//double cosTheta = cos(radians);
		//double sinTheta = sin(radians);
		//glm::mat3 rotationMatrix = glm::mat3(
		//	cosTheta + pow(axis.x, 2) * (1 - cosTheta), axis.x * axis.y * (1 - cosTheta) - axis.z * sinTheta, axis.x * axis.z * (1 - cosTheta) + axis.y * sinTheta,
		//	axis.y * axis.x * (1 - cosTheta) + axis.z * sinTheta, cosTheta + pow(axis.y, 2) * (1 - cosTheta), axis.y * axis.z * (1 - cosTheta) - axis.x * sinTheta,
		//	axis.z * axis.x * (1 - cosTheta) - axis.y * sinTheta, axis.z * axis.y * (1 - cosTheta) + axis.x * sinTheta, cosTheta + pow(axis.z, 2) * (1 - cosTheta)
		//);

		//// Perform the rotation
		//glm::vec3 rotatedVector;
		//rotatedVector.x = rotationMatrix[0][0] * translatedVector.x + rotationMatrix[0][1] * translatedVector.y + rotationMatrix[0][2] * translatedVector.z;
		//rotatedVector.y = rotationMatrix[1][0] * translatedVector.x + rotationMatrix[1][1] * translatedVector.y + rotationMatrix[1][2] * translatedVector.z;
		//rotatedVector.z = rotationMatrix[2][0] * translatedVector.x + rotationMatrix[2][1] * translatedVector.y + rotationMatrix[2][2] * translatedVector.z;

		// Inverse translate the rotated vector
		//glm::vec3 inverseTranslatedVector = rotatedVector + center;

		//return inverseTranslatedVector;

		glm::mat4 rotationMat = glm::rotate(glm::mat4(1), radians, axis);
		glm::vec3 result = glm::vec3(rotationMat * glm::vec4(translatedVector, 1.0));
		return result + center;


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

	glm::vec3 GetRotation();

	glm::mat4 GetModelMatrix();

	glm::vec3 GetPosition();

protected:
	glm::vec3 position;
	glm::vec3 scale;
	float degreesOX;
	float degreesOY;
	float degreesOZ;
};
