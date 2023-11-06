#include "lab_m1/tema1/objects/Square.h"

Square::Square(const char* name, glm::vec2 position) : Object_2D(name, position) {
}

Square::~Square() {
}

void Square::InitVertices()
{
	vertices.insert(vertices.end(), {
		// position, color, norm
		VertexFormat(glm::vec3(-1, -1, 0), glm::vec3(0, 1, 1), glm::vec3(0, 1, 0)), // A - 0
		VertexFormat(glm::vec3(-1, 1, 0), glm::vec3(0, 1, 1), glm::vec3(0, 1, 0)), // B - 1
		VertexFormat(glm::vec3(1, 1, 0), glm::vec3(0, 1, 1), glm::vec3(0, 1, 0)), // C - 2
		VertexFormat(glm::vec3(1, -1, 0), glm::vec3(0, 1, 1), glm::vec3(0, 1, 0)), // D - 3
		});

	indices.insert(indices.end(), {
		0, 1, 2, // ABC
		0, 2, 3// ACD
		});
}