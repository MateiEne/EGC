#pragma once

#include "core/world.h"
#include "core/engine.h"
#include "core/gpu/mesh.h"
#include "core/gpu/shader.h"
#include "core/gpu/texture2D.h"
#include "core/managers/resource_path.h"
#include "core/managers/texture_manager.h"

#include "utils/text_utils.h"
#include "utils/memory_utils.h"
#include "utils/gl_utils.h"
#include "utils/math_utils.h"

#include <iostream>
#include <vector>

using namespace std;

class Object_2D {
public: 
	Object_2D(const char* name, glm::vec3 position);
	virtual ~Object_2D();

	void Init();

	Mesh* GetMesh();
	glm::vec3 GetPosition();
protected:
	glm::vec3 position;
	std::vector<VertexFormat> vertices;
	std::vector<unsigned int> indices;
	const char* name;

	Mesh* objectMesh;

	void CreateMesh();
	virtual void InitVertices() = 0;
};