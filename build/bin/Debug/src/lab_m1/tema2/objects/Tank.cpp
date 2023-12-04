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
	const string& wheelFileName,
	glm::vec3 baseColor,
	glm::vec3 turretColor,
	glm::vec3 gunColor,
	glm::vec3 wheelColor
) {
	this->baseColor = baseColor;
	this->turretColor = turretColor;
	this->gunColor = gunColor;
	this->wheelColor = wheelColor;

	baseMesh = new Mesh("base");
	baseMesh->LoadMesh(fileLocation, baseFileName);

	turretMesh = new Mesh("turret");
	turretMesh->LoadMesh(fileLocation, turretFileName);

	gunMesh = new Mesh("gun");
	gunMesh->LoadMesh(fileLocation, gunFileName);

	wheelMesh = new Mesh("wheel");
	wheelMesh->LoadMesh(fileLocation, wheelFileName);

	RotateOY(90);
}

void Tank::Update(float dt) {
	for (int i = 0; i < missiles.size(); i++) {
		missiles[i]->Update(dt);

		if (missiles[i]->IsDead()) {
			missiles.erase(missiles.begin() + i);

			i--;
		}
	}
}

void Tank::MoveForward(float dt) {
	Translate(glm::vec3(dt * CST::TANK_SPEED * cos(degreesOY), 0, dt * CST::TANK_SPEED * sin(degreesOY)));
}

void Tank::MoveBackwards(float dt) {
	Translate(glm::vec3(-dt * CST::TANK_SPEED * cos(degreesOY), 0, -dt * CST::TANK_SPEED * sin(degreesOY)));
}

void Tank::RotateRight(float dt) {
	RotateOY(-dt * CST::TANK_ROTATION_SPEED);
}

void Tank::RotateLeft(float dt) {
	RotateOY(dt * CST::TANK_ROTATION_SPEED);
}

glm::vec3 Tank::GetGunHeadPosition() {
	return glm::vec3(GetPosition().x + 3 * cos(degreesOY), CST::TANK_GUN_INITIAL_POS.y, GetPosition().z + 3 * sin(degreesOY));
}

glm::vec3 Tank::GetDirection() {
	return glm::vec3(cos(degreesOY), 0, sin(degreesOY));
}

glm::vec3 Tank::GetUpDirection() {
	return glm::vec3(0, 1, 0);
}

void Tank::Fire() {
	Missile* missile = new Missile();
	missile->Init(CST::TANK_ASSETS_FILE_LOCATION, "missile.obj", GetGunHeadPosition(), GetDirection(), CST::COLORS.at("black"));
	missile->SetScale(.2f, .2f, .2f);

	missiles.push_back(missile);
}

void Tank::Draw(Shader* shader, glm::mat4 viewMatrix, glm::mat4 projectionMatrix) {
	if (!shader || !shader->program) {
		return;
	}

	// Render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	int viewMatrixLocation = glGetUniformLocation(shader->GetProgramID(), "View");
	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	int projectionMatrixLocation = glGetUniformLocation(shader->GetProgramID(), "Projection");
	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	DrawPart(baseMesh, shader, CST::TANK_BASE_INITIAL_POS, baseColor);
	DrawPart(turretMesh, shader, CST::TANK_TURRET_INITIAL_POS, turretColor);
	DrawPart(gunMesh, shader, CST::TANK_GUN_INITIAL_POS, gunColor);
	DrawPart(wheelMesh, shader, CST::TANK_RIGHT_WHEEL_INITIAL_POS, wheelColor);
	DrawPart(wheelMesh, shader, CST::TANK_LEFT_WHEEL_INITIAL_POS, wheelColor);

	for each (auto missile in missiles) {
		missile->Draw(shader, viewMatrix, projectionMatrix);
	}
}

void Tank::DrawPart(Mesh* mesh, Shader* shader, glm::vec3 partOffset, glm::vec3 color) {
	if (!mesh) {
		return;
	}
	
	// TODO(student): Get shader location for uniform mat4 "Model"
	int modelMatrixLocation = glGetUniformLocation(shader->GetProgramID(), "Model");
	// TODO(student): Set shader uniform "Model" to modelMatrix
	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(GetModelMatrix() * T3D::Translate(partOffset.x, partOffset.y, partOffset.z)));

	int objectColorLocation = glGetUniformLocation(shader->GetProgramID(), "objectColor");
	glUniform3fv(objectColorLocation, 1, glm::value_ptr(color));

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->m_VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}

