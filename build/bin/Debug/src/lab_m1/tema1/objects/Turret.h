#pragma once

#include "components/simple_scene.h"

#include "core/gpu/vertex_format.h"

#include <vector>

class Turret {
public:
	Turret(const char* name, glm::vec3 position);
	~Turret();

	void Init();

	Mesh* GetMesh();
	glm::vec3 GetPosition();
private:
	glm::vec3 position;

private:
	// position,
	std::vector<VertexFormat> vertices;
	std::vector<unsigned int> indices;
	const char* name;

	Mesh* turretMesh;

	void CreateMesh();
};