#pragma once

#include <iostream>
#include <string>

#include "lab_m1/tema2/Transform3D.h"
#include "lab_m1/tema2/Constants.h"
#include "lab_m1/tema2/BoxCollider.h"

#include "core/gpu/shader.h"
#include "core/gpu/mesh.h"

using namespace std;

class Building : public Transform3D, public BoxCollider {
public:
	Building();
	~Building();

	void Init(
		const string& fileLocation,
		const string& buildingFileName,
		glm::vec3 color
	);

	void Update(float dt);

	float GetLength() override;
	float GetHeight() override;
	float GetWidth() override;

	glm::vec3 GetCenter() override;

	void Draw(Shader* shader, glm::mat4 viewMatrix, glm::mat4 projectionMatrix);

private:
	float CalculateLength();
	float CalculateHeight();
	float CalculateWidth();

private:
	float length;
	float width;
	float height;

	Mesh* mesh;

	glm::vec3 color;
};