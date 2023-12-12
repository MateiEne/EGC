#include "Building.h"

Building::Building() {
}

Building::~Building() {
}

void Building::Init(const string& fileLocation, const string& buildingFileName, glm::vec3 color) {
	mesh = new Mesh("building");
	mesh->LoadMesh(fileLocation, buildingFileName);

	this->color = color;
}

void Building::Update(float dt) {
}

float Building::GetRadius() {
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

float Building::GetLength() {
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

	return (maxPoint.x - minPoint.x) * scale.x;
}

float Building::GetHeight() {
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

float Building::GetWidth() {
	float maxX = -10;
	float maxY = -10;
	float maxZ = -10;

	float minX = 10;
	float minY = 10;
	float minZ = 10;

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

		if (pos.z <= minZ) {
			minZ = pos.z;

			if (pos.x <= minX) {
				minX = pos.x;

				if (pos.y <= minY) {
					minY = pos.y;

					minPoint = pos;
				}
			}
		}
	}

	return (maxPoint.z - minPoint.z) * scale.z;
}

void Building::Draw(Shader* shader, glm::mat4 viewMatrix, glm::mat4 projectionMatrix) {
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
