#include "lab_m1/tema1/objects/Turret.h"

Turret::Turret(const char* name, glm::vec2 position, glm::vec3 color, int cost) : Object_2D(name, position, color) {
	this->cost = cost;

	for (int i = 0; i < cost; i++) {
		Projectile* priceStar = new Projectile("Cost", glm::vec2(0, 0), glm::vec3(192 / 256.f, 192 / 256.f, 192 / 256.f));
		priceStar->Init();

		prices.push_back(priceStar);
	}
}

Turret::~Turret() {
}

void Turret::InitVertices()
{
	vertices.insert(vertices.end(), {
		// position, color, norm
		VertexFormat(glm::vec3(-0.5f, 0.f, 0.f), color, glm::vec3(0, 1, 0)), // A - 0
		VertexFormat(glm::vec3(0.f, 1.f, 0.f), color, glm::vec3(0, 1, 0)), // B - 1
		VertexFormat(glm::vec3(0.5f, 0.f, 0.f), color, glm::vec3(0, 1, 0)), // C - 2
		VertexFormat(glm::vec3(0.f, -1.f, 0.f), color, glm::vec3(0, 1, 0)), // D - 3
		VertexFormat(glm::vec3(0.f, 0.2f, 0.f), color, glm::vec3(0, 1, 0)), // E - 4
		VertexFormat(glm::vec3(0.f, -0.2f, 0.f), color, glm::vec3(0, 1, 0)), // F - 5
		VertexFormat(glm::vec3(1.2f, -0.2f, 0.f), color, glm::vec3(0, 1, 0)), // G - 6
		VertexFormat(glm::vec3(1.2f, 0.2f, 0), color, glm::vec3(0, 1, 0)), // H - 7
		});

	indices.insert(indices.end(), {
		0, 1, 2, // ABC
		0, 2, 3, // ACD
		5, 4, 7, // FEH
		5, 7, 6, // FHG
		});
}

vector<Projectile*> Turret::GetPrices()
{
	return prices;
}

int Turret::GetCost() {
	return cost;
}
