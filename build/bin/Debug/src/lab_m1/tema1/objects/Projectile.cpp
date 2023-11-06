#include "lab_m1/tema1/objects/Projectile.h"

Projectile::Projectile(const char* name, glm::vec2 position, glm::vec3 color) : Object_2D(name, position, color) {
}

Projectile::~Projectile() {
}


void Projectile::InitVertices()
{
	vertices.insert(vertices.end(), {
		// position, color, norm
		VertexFormat(glm::vec3(0, 2, 0), color, glm::vec3(0, 1, 0)), // A - 0
		VertexFormat(glm::vec3(1.5f, 1, 0), color, glm::vec3(0, 1, 0)), // F - 1
		VertexFormat(glm::vec3(1.5f, -1, 0), color, glm::vec3(0, 1, 0)), // B - 2
		VertexFormat(glm::vec3(0, -2, 0), color, glm::vec3(0, 1, 0)), // D - 3
		VertexFormat(glm::vec3(-1.5f, -1, 0), color, glm::vec3(0, 1, 0)), // C - 4
		VertexFormat(glm::vec3(-1.5f, 1, 0), color, glm::vec3(0, 1, 0)), // E - 5
		});

	indices.insert(indices.end(), {
		0, 2, 4, // ABC
		5, 1, 3, // EFD
		});
}