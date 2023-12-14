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

	radius = CalculateRadius();
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


float Missile::CalculateRadius()
{
	float maxX = -10;
	float maxY = -10;
	float maxZ = -10;

	glm::vec3 maxPoint = glm::vec3(0);

	for each (auto pos in mesh->positions) {
		if (abs(pos.x) > maxX) {
			maxX = abs(pos.x);
			maxPoint = pos;
		}
		if (abs(pos.y) > maxY) {
			maxY = abs(pos.y);
			maxPoint = pos;
		}
		if (abs(pos.z) > maxZ) {
			maxZ = abs(pos.z);
			maxPoint = pos;
		}
	}

	float distanceXOZ = sqrt(pow(maxPoint.x * scale.x, 2) + pow(maxPoint.z * scale.z, 2));
	float distanceY = maxPoint.y * scale.y;

	float radius = sqrt(pow(distanceXOZ, 2) + pow(distanceY, 2));

	return radius;
}


float Missile::GetRadius() {
	return radius * max(max(scale.x, scale.y), scale.z);;
}

glm::vec3 Missile::GetCenter() {
	return position;
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