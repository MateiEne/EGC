#include "Tank.h"

Tank::Tank() {
}

Tank::~Tank() {
}

void Tank::Init(
	const string& fileLocation,
	const string& baseFileName,
	const string& turretFileName,
	const string& gunFileName,
	const string& wheelFileName
) {
	baseMesh = new Mesh("base");
	baseMesh->LoadMesh(fileLocation, baseFileName);

	turretMesh = new Mesh("turret");
	turretMesh->LoadMesh(fileLocation, turretFileName);

	gunMesh = new Mesh("gun");
	gunMesh->LoadMesh(fileLocation, gunFileName);

	wheelMesh = new Mesh("wheel");
	wheelMesh->LoadMesh(fileLocation, wheelFileName);

}

void Tank::Update(float dt) {

}

void Tank::Draw(Shader* shader, glm::mat4 viewMatrix, glm::mat4 projectionMatrix) {
	if (!shader || !shader->program) {
		return;
	}

	// Render an object using the specified shader and the specified position
	shader->Use();
	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	SetPosition(0, 0.2, 0);
	DrawMesh(baseMesh, shader, viewMatrix, projectionMatrix);

	SetPosition(0, 0.55, 0);
	DrawMesh(turretMesh, shader, viewMatrix, projectionMatrix);

	SetPosition(1.0268, 0.55, 0);
	DrawMesh(gunMesh, shader, viewMatrix, projectionMatrix);

	SetPosition(0, -0.01, 0.35);
	DrawMesh(wheelMesh, shader, viewMatrix, projectionMatrix);

	SetPosition(0, -0.01, -0.35);
	DrawMesh(wheelMesh, shader, viewMatrix, projectionMatrix);
}

void Tank::DrawMesh(Mesh* mesh, Shader* shader, glm::mat4 viewMatrix, glm::mat4 projectionMatrix) {
	if (!mesh) {
		return;
	}

	// Render an object using the specified shader and the specified position
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(GetModelMatrix()));

	mesh->Render();
}

