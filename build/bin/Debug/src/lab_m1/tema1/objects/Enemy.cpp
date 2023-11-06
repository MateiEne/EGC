#include "lab_m1/tema1/objects/Enemy.h"

Enemy::Enemy(const char* name, glm::vec3 position) : Object_2D(name, position) {
}

Enemy::~Enemy() {
}

void Enemy::InitVertices()
{
	vertices.insert(vertices.end(), {
		// position, color, norm
		VertexFormat(glm::vec3(-1, 0.4f, -1), glm::vec3(0, 1, 1), glm::vec3(0, 1, 0)), // A - 0
		VertexFormat(glm::vec3(0, 1, -1), glm::vec3(0, 1, 1), glm::vec3(0, 1, 0)), // B - 1
		VertexFormat(glm::vec3(1, 0.4f, -1), glm::vec3(0, 1, 1), glm::vec3(0, 1, 0)), // C - 2
		VertexFormat(glm::vec3(1, -0.4f, -1), glm::vec3(0, 1, 1), glm::vec3(0, 1, 0)), // D - 3
		VertexFormat(glm::vec3(0, -1, -1), glm::vec3(0, 1, 1), glm::vec3(0, 1, 0)), // E - 4
		VertexFormat(glm::vec3(-1, -0.4f, -1), glm::vec3(0, 1, 1), glm::vec3(0, 1, 0)), // F - 5
		VertexFormat(glm::vec3(0, 0.4f, 0), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0)), // G - 6
		VertexFormat(glm::vec3(0.4f, 0.2f, 0), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0)), // H - 7
		VertexFormat(glm::vec3(0.4f, -0.2f, 0), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0)), // I - 8
		VertexFormat(glm::vec3(0, -0.4f, 0), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0)), // J - 9
		VertexFormat(glm::vec3(-0.4f, -0.2f, 0), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0)), // K - 10
		VertexFormat(glm::vec3(-0.4f, 0.2f, 0), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0)), // L - 11
		});

	indices.insert(indices.end(), {
		0, 1, 2, // ABC
		0, 2, 3, // ACD
		0, 3, 4, // ADE
		0, 4, 5, // AEF
		11, 6, 7, // LGH
		11, 7, 8, // LHI
		11, 8, 9, // LIJ
		11, 9, 10, // LJK
		});
}