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
	glm::vec3 wheelColor,
	glm::vec3 baseOffset,
	glm::vec3 turretOffset,
	glm::vec3 gunOffset,
	glm::vec3 rightWheelOffset,
	glm::vec3 leftWheelOffset
) {
	this->fileLocation = fileLocation;

	this->baseColor = baseColor;
	this->turretColor = turretColor;
	this->gunColor = gunColor;
	this->wheelColor = wheelColor;

	this->baseOffset = baseOffset;
	this->turretOffset = turretOffset;
	this->gunOffset = gunOffset;
	this->rightWheelOffset = rightWheelOffset;
	this->leftWheelOffset = leftWheelOffset;

	baseMesh = new Mesh("base");
	baseMesh->LoadMesh(fileLocation, baseFileName);

	turretMesh = new Mesh("turret");
	turretMesh->LoadMesh(fileLocation, turretFileName);

	gunMesh = new Mesh("gun");
	gunMesh->LoadMesh(fileLocation, gunFileName);

	wheelMesh = new Mesh("wheel");
	wheelMesh->LoadMesh(fileLocation, wheelFileName);

	SetPosition(0, -GetLowestPoint().y - leftWheelOffset.y, 0);
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
	return glm::vec3(GetPosition().x + 3 * cos(degreesOY), gunOffset.y, GetPosition().z + 3 * sin(degreesOY));
}

glm::vec3 Tank::GetLowestPoint() {
	glm::vec3 lowestPoint = glm::vec3(0);

	float yMin = 1000;

	for each (auto pos in wheelMesh->positions) {
		if (pos.y < yMin) {
			yMin = pos.y;

			lowestPoint = pos;
		}
	}

	return lowestPoint;
}

float Tank::GetHeight() {
	float height = 0;

	float yMin = 1000;
	float yMax = -1000;

	for each (auto pos in wheelMesh->positions) {
		if (pos.y < yMin) {
			yMin = pos.y;
		}
	}
	height += yMin - leftWheelOffset.y;

	for each (auto pos in baseMesh->positions) {
		if (pos.y > yMax) {
			yMax = pos.y;
		}
	}
	height += yMax + baseOffset.y;
	yMax = -1000;

	for each (auto pos in turretMesh->positions) {
		if (pos.y > yMax) {
			yMax = pos.y;
		}
	}
	height += yMax + turretOffset.y;


	return height;
}

float Tank::GetBaseRadius() {
	float maxX = -10;
	float maxY = -10;
	float maxZ = -10;

	glm::vec3 maxPoint = glm::vec3(0);

	for each (auto pos in baseMesh->positions) {
		if (abs(pos.x + baseOffset.x) > maxX) {
			maxX = abs(pos.x);
			maxPoint = pos;
		}
		if (abs(pos.y + baseOffset.y) > maxY) {
			maxY = abs(pos.y);
			maxPoint = pos;
		}
		if (abs(pos.z + baseOffset.z) > maxZ) {
			maxZ = abs(pos.z);
			maxPoint = pos;
		}
	}

	float distanceXOZ = sqrt(pow(maxPoint.x * scale.x, 2) + pow(maxPoint.z * scale.z, 2));
	float distanceY = maxPoint.y * scale.y;

	float radius = sqrt(pow(distanceXOZ, 2) + pow(distanceY, 2));

	return radius;
}

bool Tank::IsInCollisionWithTank(Tank* tank) {
	float distanceXOZ = sqrt(pow((position.x - tank->position.x), 2) + pow((position.z - tank->position.z), 2));
	float distanceY = position.y - tank->position.y;

	float distance = sqrt(pow(distanceXOZ, 2) + pow(distanceY, 2));

	return distance < (GetBaseRadius() + tank->GetBaseRadius());
}

bool Tank::IsInCollisionWithBuilding(Building* building) {
	float buildingMinX = building->GetPosition().x - building->GetLength() / 2;
	float buildingMinY = building->GetPosition().y - building->GetHeight() / 2;
	float buildingMinZ = building->GetPosition().z - building->GetWidth() / 2;

	float buildingMaxX = building->GetPosition().x + building->GetLength() / 2;
	float buildingMaxY = building->GetPosition().y + building->GetHeight() / 2;
	float buildingMaxZ = building->GetPosition().z + building->GetWidth() / 2;
		
	float x = max(buildingMinX, min(position.x, buildingMaxX));
	float y = max(buildingMinY, min(position.y, buildingMaxY));
	float z = max(buildingMinZ, min(position.z, buildingMaxZ));

	float distance = sqrt(pow((x - position.x), 2) + pow((y - position.y), 2) + pow((z - position.z), 2));

	return distance < GetBaseRadius();
}

glm::vec3 Tank::GetDirection() {
	return glm::vec3(cos(degreesOY), 0, sin(degreesOY));
}

glm::vec3 Tank::GetUpDirection() {
	return glm::vec3(0, 1, 0);
}

void Tank::Fire() {
	Missile* missile = new Missile();
	missile->Init(fileLocation, "missile.obj", GetGunHeadPosition(), GetDirection(), CST::COLORS.at("black"));
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

	DrawPart(baseMesh, shader, baseOffset, baseColor);
	DrawPart(turretMesh, shader, turretOffset, turretColor);
	DrawPart(gunMesh, shader, gunOffset, gunColor);
	DrawPart(wheelMesh, shader, rightWheelOffset, wheelColor);
	DrawPart(wheelMesh, shader, leftWheelOffset, wheelColor);

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

