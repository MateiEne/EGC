#include "lab_m1/tema1/objects/Square.h"

Square::Square(const char* name, glm::vec2 position, glm::vec3 color) : Object_2D(name, position, color) {
}

Square::~Square() {
}

void Square::InitVertices() {
	vertices.insert(vertices.end(), {
		// position, color, norm
		VertexFormat(glm::vec3(-0.5f, -0.5f, 0), color, glm::vec3(0, 1, 0)), // A - 0
		VertexFormat(glm::vec3(-0.5f, 0.5f, 0), color, glm::vec3(0, 1, 0)), // B - 1
		VertexFormat(glm::vec3(0.5f, 0.5f, 0), color, glm::vec3(0, 1, 0)), // C - 2
		VertexFormat(glm::vec3(0.5f, -0.5f, 0), color, glm::vec3(0, 1, 0)), // D - 3
		});

	indices.insert(indices.end(), {
		0, 1, 2, // ABC
		0, 2, 3// ACD
		}
	);

	width = 1;
	height = 1;
}

bool Square::IsCoordInObject(glm::vec2 coord) {
	return Object_2D::IsCoordInObject(coord);

	cout << coord;

	if (coord.x < (position.x + GetWidth() / 2) && (coord.x > (position.x - GetWidth() / 2))) {
		if (coord.y < (position.y + GetHeight() / 2) && (coord.y > (position.y - GetHeight() / 2))) {
			return true;
		}
	}

	return false;
}

float Square::GetHeight() {
	return scale.y * height;
}

float Square::GetWidth()
{
	return scale.x * width;
}