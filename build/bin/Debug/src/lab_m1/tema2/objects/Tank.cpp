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

void Tank::MoveForward(float dt) {
	Translate(glm::vec3(dt * CST::TANK_SPEED * cos(degreesOY), 0, dt * CST::TANK_SPEED * sin(degreesOY)));
}

void Tank::MoveBackwards(float dt) {
	Translate(glm::vec3(-dt * CST::TANK_SPEED * cos(degreesOY), 0, -dt * CST::TANK_SPEED * sin(degreesOY)));
}

void Tank::RotateRight(float dt) {
	RotateOY(dt * CST::TANK_ROTATION_SPEED);
}

void Tank::RotateLeft(float dt) {
	RotateOY(-dt * CST::TANK_ROTATION_SPEED);
}

void Tank::Draw(Shader* shader, glm::mat4 viewMatrix, glm::mat4 projectionMatrix) {
	if (!shader || !shader->program) {
		return;
	}

	// Render an object using the specified shader and the specified position
	shader->Use();
	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	DrawPart(baseMesh, shader, CST::TANK_BASE_INITIAL_POS);
	DrawPart(turretMesh, shader, CST::TANK_TURRET_INITIAL_POS);
	DrawPart(gunMesh, shader, CST::TANK_GUN_INITIAL_POS);
	DrawPart(wheelMesh, shader, CST::TANK_RIGHT_WHEEL_INITIAL_POS);
	DrawPart(wheelMesh, shader, CST::TANK_LEFT_WHEEL_INITIAL_POS);
}

void Tank::DrawPart(Mesh* mesh, Shader* shader, glm::vec3 translation) {
	if (!mesh) {
		return;
	}

	// Render an object using the specified shader and the specified position
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(
		GetModelMatrix() * T3D::Translate(translation.x, translation.y, translation.z)
	));

	mesh->Render();
}

