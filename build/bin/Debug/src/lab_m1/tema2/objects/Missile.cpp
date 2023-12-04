#include "Missile.h"

Missile::Missile() {
	isDead = false;
}

Missile::~Missile() {
}

void Missile::Init(
	const string& fileLocation,
	const string& missileFileName,
	glm::vec3 initialPosition,
	glm::vec3 direction,
	glm::vec3 color
) {
	mesh = new Mesh("missile");
	mesh->LoadMesh(fileLocation, missileFileName);

	this->initialPosition = initialPosition;
	this->direction = direction;

	SetPosition(initialPosition);

	this->color = color;
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
	glUseProgram(shader->program);

	int viewMatrixLocation = glGetUniformLocation(shader->GetProgramID(), "View");
	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	int projectionMatrixLocation = glGetUniformLocation(shader->GetProgramID(), "Projection");
	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	// Render an object using the specified shader and the specified position
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(GetModelMatrix()));

	int objectColorLocation = glGetUniformLocation(shader->GetProgramID(), "objectColor");
	glUniform3fv(objectColorLocation, 1, glm::value_ptr(color));

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->m_VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}
