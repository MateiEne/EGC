#pragma once

#include "components/simple_scene.h"

//#include "core/gpu/vertex_format.h"

#include <vector>

class Turret : public gfxc::SimpleScene {
public:
	Turret(const char* name);
	~Turret();

	void CreateTurret(const std::vector<VertexFormat>& vertices,
		const std::vector<unsigned int>& indices);
	const char* GetName();
	void Render(glm::vec3 position, glm::vec3 scale);
private:
	const char* name;
	//const std::vector<VertexFormat> vertices;
	//const std::vector<unsigned int> indices;

protected:
};