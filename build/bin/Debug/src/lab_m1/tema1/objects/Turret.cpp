#include "lab_m1/tema1/objects/Turret.h"

Turret::Turret(const char* name, glm::vec3 position) : Object_2D(name, position) {
}

Turret::~Turret() {
}

void Turret::InitVertices()
{
	vertices.insert(vertices.end(), {
		// position, color, norm
		VertexFormat(glm::vec3(-1, 0, 0), glm::vec3(0, 1, 1), glm::vec3(0, 1, 0)), // A - 0
		VertexFormat(glm::vec3(0, 2, 0), glm::vec3(0, 1, 1), glm::vec3(0, 1, 0)), // B - 1
		VertexFormat(glm::vec3(1, 0, 0), glm::vec3(0, 1, 1), glm::vec3(0, 1, 0)), // C - 2
		VertexFormat(glm::vec3(0, -2, 0), glm::vec3(0, 1, 1), glm::vec3(0, 1, 0)), // D - 3
		VertexFormat(glm::vec3(0, 1, 0), glm::vec3(0, 1, 1), glm::vec3(0, 1, 0)), // E - 4
		VertexFormat(glm::vec3(2, 1, 0), glm::vec3(0, 1, 1), glm::vec3(0, 1, 0)), // F - 5
		VertexFormat(glm::vec3(2, -1, 0), glm::vec3(0, 1, 1), glm::vec3(0, 1, 0)), // G - 6
		VertexFormat(glm::vec3(0, -1, 0), glm::vec3(0, 1, 1), glm::vec3(0, 1, 0)), // H - 7
		});

	indices.insert(indices.end(), {
		0, 1, 2, // ABC
		0, 2, 3, // ACD
		7, 4, 5, // HEF
		7, 5, 6, // HFG
		});
}