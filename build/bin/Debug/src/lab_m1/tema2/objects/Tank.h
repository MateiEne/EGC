#pragma once

#include <string>
#include "core/gpu/mesh.h"
#include "core/gpu/shader.h"
#include "components/camera.h"

using namespace std;

class Tank {
public:
	Tank();
	~Tank();

	void Init(
		const string& fileLocation,
		const string& baseFileName, 
		const string& turretFileName, 
		const string& gunFileName, 
		const string& wheelFileName
	);
	void Draw(Shader* shader, glm::mat4 viewMatrix, glm::mat4 projectionMatrix);

private:
	Mesh* baseMesh;
	Mesh* turretMesh;
	Mesh* gunMesh;
	Mesh* wheelMesh;

	glm::mat4 modelMatrix;
};