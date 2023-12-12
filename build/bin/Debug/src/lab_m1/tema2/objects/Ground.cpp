#include "Ground.h"

Ground::Ground() {
}

Ground::~Ground() {
}

void Ground::Init(const string& fileLocation, const string& groundFileName, glm::vec3 color) {
	mesh = new Mesh("ground");
	mesh->LoadMesh(fileLocation, groundFileName);

	SetScale(CST::WORLD_SCALE_X, CST::WORLD_SCALE_Y, CST::WORLD_SCALE_Z);

	this->color = color;
}

float Ground::GetHeight() {
	float maxX = -10;
	float maxY = -10;
	float maxZ = -10;

	float minX = 10;
	float minY = 10;

	glm::vec3 maxPoint = glm::vec3(0);
	glm::vec3 minPoint = glm::vec3(0);

	for each (auto pos in mesh->positions) {
		if (pos.z >= maxZ) {
			maxZ = pos.z;

			if (pos.x >= maxX) {
				maxX = pos.x;

				if (pos.y >= maxY) {
					maxY = pos.y;

					maxPoint = pos;
				}
			}
		}

		if (pos.z >= maxZ) {
			maxZ = pos.z;

			if (pos.x <= minX) {
				minX = pos.x;

				if (pos.y <= minY) {
					minY = pos.y;

					minPoint = pos;
				}
			}
		}
	}

	return (maxPoint.y - minPoint.y) * scale.y;
}

void Ground::Update(float dt) {
}

void Ground::Draw(Shader* shader, glm::mat4 viewMatrix, glm::mat4 projectionMatrix) {
	if (!shader || !shader->program || !mesh) {
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
