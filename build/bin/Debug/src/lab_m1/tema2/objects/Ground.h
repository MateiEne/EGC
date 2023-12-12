#pragma once

#include <iostream>
#include <string>
#include "core/gpu/mesh.h"
#include "core/gpu/shader.h"

#include "lab_m1/tema2/Transform3D.h"
#include "lab_m1/tema2/Constants.h"

using namespace std;

class Ground : public Transform3D {
public:
	Ground();
	~Ground();

	void Init(
		const string& fileLocation,
		const string& groundFileName, 
		glm::vec3 color
	);

	void Update(float dt);

	float GetHeight();

	void Draw(Shader* shader, glm::mat4 viewMatrix, glm::mat4 projectionMatrix);

private:
	Mesh* mesh;

	glm::vec3 color;
};