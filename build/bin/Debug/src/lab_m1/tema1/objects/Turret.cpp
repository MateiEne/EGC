#include "lab_m1/tema1/objects/Turret.h"

Turret::Turret(const char* name, glm::vec2 position, glm::vec3 color, int cost) : Object_2D(name, position, color) {
	this->cost = cost;

	projectile = nullptr;

	timeCounter = TIME_TO_FIRE;

	isDestroied = false;

	scaleFactorDestroy = 1;
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

int Turret::GetCost() {
	return cost;
}

void Turret::Fire() {
	if (projectile != nullptr || timeCounter < TIME_TO_FIRE) {
		return;
	}

	projectile = new Projectile("projectile", glm::vec2(0, 0), color);
	projectile->Init();

	projectile->SetPosition(position.x + GetRadius(), position.y);
	projectile->SetScale(PROJECTILE_SCALE);

	timeCounter = 0;
}

void Turret::Update(float deltaTime) {
	if (isDestroied) {
		if (GetRadius() >= TURRET_MIN_DESTROY_RADIUS) {
			Scale(1 - deltaTime * TURRET_DESTROY_SCALE_SPEED, 1 - deltaTime * TURRET_DESTROY_SCALE_SPEED);
		}

		return;
	}
	
	timeCounter += deltaTime;

	if (projectile == nullptr) {
		return;
	}

	projectile->Translate(deltaTime * PROJECTILE_SPEED, 0);
	projectile->Rotate(PROJECTILE_ROTATION * -deltaTime);

	if (projectile->GetPosition().x > CAMERA_ORTHO_WIDTH) {
		delete projectile;
		projectile = nullptr;
	}
}

void Turret::Destroy() {
	isDestroied = true;
}

bool Turret::ShouldRemove() {
	return GetRadius() <= TURRET_MIN_DESTROY_RADIUS;
}

void Turret::Draw(Shader* shader, const glm::mat4 viewMatrix, const glm::mat4 projectionMatrix) {
	Object_2D::Draw(shader, viewMatrix, projectionMatrix);

	if (projectile != nullptr) {
		projectile->Draw(shader, viewMatrix, projectionMatrix);
	}
}

Projectile* Turret::GetProjectile() {
	return projectile;
}

void Turret::RemoveProjectile() {
	if (projectile == nullptr) {
		return;
	}

	delete projectile;
	projectile = nullptr;
}
