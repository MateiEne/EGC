#include "Missile.h"

Missile::Missile(glm::vec3 initialPosition, glm::vec3 direction) {
	this->initialPosition = initialPosition;
	this->direction = direction;

	isDead = false;
}

Missile::~Missile() {
}

void Missile::Init(
	const string& fileLocation,
	const string& missileFileName
) {
	mesh = new Mesh("missile");
	mesh->LoadMesh(fileLocation, missileFileName);

	SetPosition(initialPosition);
}

void Missile::Update(float dt) {
	if (isDead == true) {
		return;
	}

	if (position.x > initialPosition.x + 20
		|| position.x < initialPosition.x - 20
		|| position.z > initialPosition.z + 20
		|| position.z < initialPosition.z - 20) {
		isDead = true;

		return;
	}

	Translate(dt * direction * CST::MISSILE_SPEED);
}

bool Missile::IsDead() {
	return isDead;
}

glm::vec3 Missile::GetDirection() {
	return direction;
}

void Missile::Draw(Shader* shader, glm::mat4 viewMatrix, glm::mat4 projectionMatrix) {
	if (!shader || !shader->program || !mesh || isDead) {
		return;
	}

	// Render an object using the specified shader and the specified position
	shader->Use();
	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	// Render an object using the specified shader and the specified position
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(GetModelMatrix()));

	mesh->Render();
}
