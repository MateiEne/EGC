#include "lab_m1/tema1/objects/Projectile.h"

Projectile::Projectile(const char* name, glm::vec2 position, glm::vec3 color) : Object_2D(name, position, color) {
}

Projectile::~Projectile() {
}


void Projectile::InitVertices()
{
	vertices.insert(vertices.end(), {
		// position, color, norm
		VertexFormat(glm::vec3(-0.5f, 0.2f, 0.f), color, glm::vec3(0, 1, 0)), // A - 0
		VertexFormat(glm::vec3(-0.12f, 0.2f, 0.f), color, glm::vec3(0, 1, 0)), // B - 1
		VertexFormat(glm::vec3(0.f, 0.5f, 0.f), color, glm::vec3(0, 1, 0)), // C - 2
		VertexFormat(glm::vec3(0.12f, 0.2f, 0.f), color, glm::vec3(0, 1, 0)), // D - 3
		VertexFormat(glm::vec3(0.5f, 0.2f, 0.f), color, glm::vec3(0, 1, 0)), // E - 4
		VertexFormat(glm::vec3(0.2f, 0.f, 0.f), color, glm::vec3(0, 1, 0)), // F - 5
		VertexFormat(glm::vec3(0.4f, -0.5f, 0.f), color, glm::vec3(0, 1, 0)), // G - 6
		VertexFormat(glm::vec3(0.f, -0.2f, 0.f), color, glm::vec3(0, 1, 0)), // H - 7
		VertexFormat(glm::vec3(-0.4f, -0.5f, 0.f), color, glm::vec3(0, 1, 0)), // I - 8
		VertexFormat(glm::vec3(-0.2f, 0.f, 0.f), color, glm::vec3(0, 1, 0)), // J - 9
		});

	indices.insert(indices.end(), {
			0, 1, 9,// ABJ
			9, 2, 5, // JCF
			3, 4, 5, // DEF
			9, 5, 7, // JFH
			9, 7, 8, // JHI
			7, 5, 6// HFG
		}
	);
}