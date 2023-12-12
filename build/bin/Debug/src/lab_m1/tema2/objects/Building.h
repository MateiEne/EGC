#pragma once

#include <iostream>
#include <string>

#include "lab_m1/tema2/Transform3D.h"
#include "lab_m1/tema2/Constants.h"

#include "core/gpu/shader.h"
#include "core/gpu/mesh.h"

using namespace std;

class Building : public Transform3D {
public:
	Building();
	~Building();

	void Init(
		const string& fileLocation,
		const string& buildingFileName,
		glm::vec3 color
	);

	void Update(float dt);

	void Draw(Shader* shader, glm::mat4 viewMatrix, glm::mat4 projectionMatrix);

private:
	Mesh* mesh;

	glm::vec3 color;
};