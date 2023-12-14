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
	glm::vec3 leftWheelOffset,
	int maxHp
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

	radius = GetBaseRadius();

	this->maxHp = maxHp;

	hp = maxHp;
}

void Tank::Update(float dt) {
	if (hp <= 0) {
		return;
	}

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

glm::vec3 Tank::GetCenter() {
	return position;
}

float Tank::GetRadius() {
	return radius * max(max(scale.x, scale.y), scale.z);
}

void Tank::TakeDamage(Collider* collider) {
	if (Missile* m = dynamic_cast<Missile*>(collider)) {
		cout << "Asdfadsfasd" << endl;

		hp--;
	}


	cout << "hitted" << endl;
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
	SceneColliders::GetInstance().AddCollider(missile);
}

void Tank::Draw(unordered_map<std::string, Shader*> shaders, glm::mat4 viewMatrix, glm::mat4 projectionMatrix) {
	Shader* shader = shaders["TankShaders"];
	
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
		missile->Draw(shaders["TemaShaders"], viewMatrix, projectionMatrix);
	}
}

void Tank::DrawPart(Mesh* mesh, Shader* shader, glm::vec3 partOffset, glm::vec3 color) {
	if (hp <= 0) {
		return;
	}

	if (!mesh) {
		return;
	}

	// TODO(student): Get shader location for uniform mat4 "Model"
	int modelMatrixLocation = glGetUniformLocation(shader->GetProgramID(), "Model");
	// TODO(student): Set shader uniform "Model" to modelMatrix
	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(GetModelMatrix() * T3D::Translate(partOffset.x, partOffset.y, partOffset.z)));

	int objectColorLocation = glGetUniformLocation(shader->GetProgramID(), "objectColor");
	glUniform3fv(objectColorLocation, 1, glm::value_ptr(color));

	int hpLocation = glGetUniformLocation(shader->GetProgramID(), "hp");
	glUniform1i(hpLocation, hp);

	int maxHpLocation = glGetUniformLocation(shader->GetProgramID(), "maxHp");
	glUniform1i(maxHpLocation, maxHp);

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->m_VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}

void Tank::DrawDebug(unordered_map<std::string, Shader*> shaders, glm::mat4 viewMatrix, glm::mat4 projectionMatrix) {
	if (hp <= 0) {
		return;
	}

	Shader* shader = shaders["TemaShaders"];

	if (!shader || !shader->program) {
		return;
	}

	// Render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	int viewMatrixLocation = glGetUniformLocation(shader->GetProgramID(), "View");
	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	int projectionMatrixLocation = glGetUniformLocation(shader->GetProgramID(), "Projection");
	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	Mesh* mesh = new Mesh("sphere");
	mesh->LoadMesh(CST::SPHERE_ASSETS_FILE_LOCATION, "sphere.obj");
	float scale = 2 * GetBaseRadius();

	// TODO(student): Get shader location for uniform mat4 "Model"
	int modelMatrixLocation = glGetUniformLocation(shader->GetProgramID(), "Model");
	// TODO(student): Set shader uniform "Model" to modelMatrix
	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(GetModelMatrix() * T3D::Scale(scale, scale, scale)));

	int objectColorLocation = glGetUniformLocation(shader->GetProgramID(), "objectColor");
	glUniform3fv(objectColorLocation, 1, glm::value_ptr(glm::vec3(1, 0, 0)));

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->m_VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	delete mesh;
}
