#include "lab_m1/tema1/Tema1.h"

using namespace m1;

Tema1::Tema1() {

}

Tema1::~Tema1() {

}

void Tema1::Init() {
	polygonMode = GL_FILL;

	auto camera = GetSceneCamera();
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->SetOrthographic(0, CAMERA_ORTHO_WIDTH, 0, CAMERA_ORTHO_HEIGHT, 0.01, 400);
	camera->Update();
	GetCameraInput()->SetActive(false);

	InitGameScene();
	InitHUD();

	generatedTurret = nullptr;

	cellsMatrix = glm::mat3(0);

	timeCounterMoney = 0;
	timeToSpawnRandomMoney = rand() % SPAWN_RANDOM_MONEY_INTERVAL_HIGH + SPAWN_RANDOM_MONEY_INTERVAL_LOW;
	totalMoneyNr = 10;

	totalLivesNr = 3;

	timeCounterEnemies = 0;
	timeToSpawnEnemies = rand() % SPAWN_RANDOM_ENEMIES_INTERVAL_HIGH + SPAWN_RANDOM_ENEMIES_INTERVAL_LOW;
}

void Tema1::InitGameScene() {
	base = new Square("base", glm::vec2(1, 8), glm::vec3(1, 0, 0));
	base->Init();
	base->Scale(glm::vec2(1.5, 15));

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			Square* cell = new Square("cell", glm::vec2(0, 0), GREEN_COLOR);
			cell->Init();

			cell->SetScale(3.8, 3.8);
			cell->SetPosition(j * (2 * cell->GetRadius()) + 5, i * 2 * cell->GetRadius() + 2.8f);

			if (j == i) {
				enemyPositions.push_back(glm::vec2(CAMERA_ORTHO_WIDTH, i * 2 * cell->GetRadius() + 2.8f));
			}

			cells.push_back(cell);
		}
	}

}

void m1::Tema1::InitHUD() {
	turretFrame = new Frame("turretFrame", glm::vec2(0, 0), WHITE_COLOR);
	turretFrame->Init();

	guiFrames.push_back(new GUIFrame(
		"orangeFrame",
		glm::vec2(4, 27),
		ORANGE_COLOR,
		1
	));

	guiFrames.push_back(new GUIFrame(
		"blueFrame",
		glm::vec2(12, 27),
		BLUE_COLOR,
		2
	));

	guiFrames.push_back(new GUIFrame(
		"yellowFrame",
		glm::vec2(20, 27),
		YELLOW_COLOR,
		2
	));

	guiFrames.push_back(new GUIFrame(
		"purpleFrame",
		glm::vec2(28, 27),
		PURPLE_COLOR,
		3
	));

	life = new Square("life", glm::vec2(0, 0), RED_COLOR);
	life->Init();

	money = new Projectile("money", glm::vec2(0, 0), GOLD_COLOR);
	money->Init();
}

void m1::Tema1::InitRandomMoney() {
	int n = rand() % 4 + 1;

	for (int i = 0; i < n; i++) {
		Projectile* star = new Projectile("star", glm::vec2(0, 0), GOLD_COLOR);
		star->Init();

		float x = (rand() % (CAMERA_ORTHO_WIDTH - 1)) + 1;
		float y = (rand() % (CAMERA_ORTHO_HEIGHT - 1)) + 1;
		star->SetPosition(x, y);
		star->SetScale(RANDOM_MONEY_SCALE);

		randomMoney.push_back(star);
	}

	timeToSpawnRandomMoney = rand() % SPAWN_RANDOM_MONEY_INTERVAL_HIGH + SPAWN_RANDOM_MONEY_INTERVAL_LOW;
}

void m1::Tema1::InitRandomEnemies() {
	int colorIndex = rand() % 4;
	int secondaryColorIndex = rand() % 3;
	int line = rand() % enemyPositions.size();

	Enemy* enemy = new Enemy("enemy", enemyPositions.at(line), BLUE_COLOR, GREY_COLOR, 3);
	enemy->Init();

	enemies.push_back(enemy);

	timeToSpawnEnemies = rand() % SPAWN_RANDOM_ENEMIES_INTERVAL_HIGH + SPAWN_RANDOM_ENEMIES_INTERVAL_LOW;
}

void Tema1::FrameStart() {
	// Clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();

	// Sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Update(float deltaTimeSeconds) {
	UpdateTimeCunterMoney(deltaTimeSeconds);
	UpdateTimeCounterEnemies(deltaTimeSeconds);

	UpdateEnemies(deltaTimeSeconds);
	UpdateTurrets(deltaTimeSeconds);

	CheckForEnemies(deltaTimeSeconds);

	DrawRandomMoney();
	DrawHUD();
	DrawScene();
}

void Tema1::UpdateTimeCunterMoney(float deltaTime) {
	timeCounterMoney += deltaTime;

	if (randomMoney.empty()) {
		if (timeCounterMoney > timeToSpawnRandomMoney) {
			InitRandomMoney();
		}
	}
}

void m1::Tema1::UpdateTimeCounterEnemies(float deltaTime) {
	timeCounterEnemies += deltaTime;

	if (timeCounterEnemies > timeToSpawnEnemies) {
		InitRandomEnemies();
		timeCounterEnemies = 0;
	}
}

void m1::Tema1::UpdateTurrets(float deltaTime) {
	for each (auto turret in placedTurrets) {
		turret->Update(deltaTime);
	}
}

void m1::Tema1::CheckForEnemies(float deltaTime) {
	for each (auto enemy in enemies) {
		for each (auto turret in placedTurrets) {
			if (turret->GetPosition().y == enemy->GetPosition().y) {
				if (enemy->IsInCollision(turret->GetProjectile())) {
					turret->RemoveProjectile();
				}

				turret->Fire();
			}
		}
	}
}

void Tema1::DrawScene() {
	glm::mat4 cameraViewMatrix = GetSceneCamera()->GetViewMatrix();
	glm::mat4 cameraProjectionMatrix = GetSceneCamera()->GetProjectionMatrix();

	DrawPojectiles();
	DrawEnemies();
	base->Draw(shaders["VertexColor"], cameraViewMatrix, cameraProjectionMatrix);

	if (!placedTurrets.empty()) {
		for each (auto turret in placedTurrets) {
			turret->Draw(shaders["VertexColor"], cameraViewMatrix, cameraProjectionMatrix);
		}
	}

	for each (auto cell in cells) {
		cell->Draw(shaders["VertexColor"], cameraViewMatrix, cameraProjectionMatrix);
	}
}

void Tema1::DrawHUD() {
	glm::mat4 cameraViewMatrix = GetSceneCamera()->GetViewMatrix();
	glm::mat4 cameraProjectionMatrix = GetSceneCamera()->GetProjectionMatrix();

	if (generatedTurret != nullptr) {
		generatedTurret->Draw(shaders["VertexColor"], cameraViewMatrix, cameraProjectionMatrix);
	}

	for each (auto frame in guiFrames) {
		frame->Draw(shaders["VertexColor"], cameraViewMatrix, cameraProjectionMatrix);
	}

	DrawLives();
	DrawTotalMoney();
}

void m1::Tema1::DrawHUDGUI(Turret* turret, int factor) {
	float turretFrameOffset = 4.f;

	glm::mat4 cameraViewMatrix = GetSceneCamera()->GetViewMatrix();
	glm::mat4 cameraProjectionMatrix = GetSceneCamera()->GetProjectionMatrix();

	for (int i = 0; i < 4; i++) {
		turretFrame->SetPosition(i * (turretFrame->GetRadius() + turretFrameOffset) + 3.f, 27);
		turretFrame->SetScale(3.8, 3.8);

		turretFrame->Draw(shaders["VertexColor"], cameraViewMatrix, cameraProjectionMatrix);
	}

	turret->SetPosition(factor * (turretFrame->GetRadius() + turretFrameOffset) + 3.f, 27);
	turret->SetScale(1.5f, 1.8f);

	turret->Draw(shaders["VertexColor"], cameraViewMatrix, cameraProjectionMatrix);
}

void m1::Tema1::DrawLives() {
	glm::mat4 cameraViewMatrix = GetSceneCamera()->GetViewMatrix();
	glm::mat4 cameraProjectionMatrix = GetSceneCamera()->GetProjectionMatrix();

	totalLivesPosX = TOTAL_LIVES_START_X;

	for (int i = 0; i < totalLivesNr; i++) {
		life->SetPosition(totalLivesPosX, TOTAL_LIVES_START_Y);
		life->SetScale(LIFE_SCALE);

		life->Draw(shaders["VertexColor"], cameraViewMatrix, cameraProjectionMatrix);

		totalLivesPosX += 1.5 * life->GetWidth();
	}
}

void m1::Tema1::DrawTotalMoney() {
	glm::mat4 cameraViewMatrix = GetSceneCamera()->GetViewMatrix();
	glm::mat4 cameraProjectionMatrix = GetSceneCamera()->GetProjectionMatrix();

	totalMoneyPosX = TOTAL_MONEY_START_X;
	totalMoneyPosY = TOTAL_MONEY_START_Y;

	for (int i = 0; i < totalMoneyNr; i++) {
		if (totalMoneyPosX + money->GetRadius() >= CAMERA_ORTHO_WIDTH) {
			totalMoneyPosY -= 2 * money->GetRadius();
			totalMoneyPosX = TOTAL_MONEY_START_X;
		}

		money->SetPosition(totalMoneyPosX, totalMoneyPosY);
		money->SetScale(TOTAL_MONEY_SCALE);

		money->Draw(shaders["VertexColor"], cameraViewMatrix, cameraProjectionMatrix);

		totalMoneyPosX += 2 * money->GetRadius();
	}
}

void m1::Tema1::DrawRandomMoney() {
	glm::mat4 cameraViewMatrix = GetSceneCamera()->GetViewMatrix();
	glm::mat4 cameraProjectionMatrix = GetSceneCamera()->GetProjectionMatrix();

	for each (auto money in randomMoney) {
		money->Draw(shaders["VertexColor"], cameraViewMatrix, cameraProjectionMatrix);
	}
}

void m1::Tema1::DrawEnemies() {
	glm::mat4 cameraViewMatrix = GetSceneCamera()->GetViewMatrix();
	glm::mat4 cameraProjectionMatrix = GetSceneCamera()->GetProjectionMatrix();

	for each (auto enemy in enemies) {
		enemy->Draw(shaders["VertexColor"], cameraViewMatrix, cameraProjectionMatrix);
		enemy->DrawDebug(shaders["VertexColor"], cameraViewMatrix, cameraProjectionMatrix);
	}
}

void m1::Tema1::DrawPojectiles() {
	glm::mat4 cameraViewMatrix = GetSceneCamera()->GetViewMatrix();
	glm::mat4 cameraProjectionMatrix = GetSceneCamera()->GetProjectionMatrix();

	//for each (auto projectile in projectiles) {
	//	projectile->Draw(shaders["VertexColor"], cameraViewMatrix, cameraProjectionMatrix);
	//}
}

void m1::Tema1::UpdateEnemies(float deltaTime) {
	for (int i = 0; i < enemies.size(); i++) {
		enemies[i]->Translate(-deltaTime * 6, 0);

		if (enemies[i]->GetPosition().x + enemies[i]->GetRadius() < base->GetPosition().x) {
			Enemy* enemyToDelete = enemies[i];

			enemies.erase(enemies.begin() + i);
			i--;

			totalLivesNr--;

			delete enemyToDelete;
		}
	}
}

glm::vec2 m1::Tema1::GetTransformedScreenCoordToWorldCoord(int screenX, int screenY) {
	glm::ivec2 resolution = window->GetResolution();

	return glm::vec2(CAMERA_ORTHO_WIDTH * (float)screenX / resolution.x, CAMERA_ORTHO_HEIGHT * (float)(resolution.y - screenY) / resolution.y);
}

void Tema1::FrameEnd() {
	DrawCoordinateSystem();
}

void m1::Tema1::OnInputUpdate(float deltaTime, int mods)
{
}

void m1::Tema1::OnKeyPress(int key, int mods) {
	if (totalLivesNr > 0) {
		if (key == GLFW_KEY_U) {
			totalLivesNr--;
		}
	}

	if (totalMoneyNr > 0) {
		if (key == GLFW_KEY_M) {
			totalMoneyNr++;
		}
	}

	if (key == GLFW_KEY_R) {
		cout << rand() % (3 - 1 + 1) + 1 << " ";
	}
}

void m1::Tema1::OnKeyRelease(int key, int mods) {

}

void m1::Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) {
	if (generatedTurret != nullptr) {
		glm::vec2 mouseWorldPosition = GetTransformedScreenCoordToWorldCoord(mouseX, mouseY);

		generatedTurret->SetPosition(mouseWorldPosition);
	}
}

void m1::Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) {
	if (button == GLFW_MOUSE_BUTTON_RIGHT) {
		glm::vec2 mouseWorldPosition = GetTransformedScreenCoordToWorldCoord(mouseX, mouseY);

		//cout << mouseWorldPosition.x << " " << mouseWorldPosition.y << endl;

		for each (auto frame in guiFrames) {
			if (frame->IsCoordInFrame(mouseWorldPosition)) {
				cout << "is in frame: " << frame->GetColor() << endl;

				if (generatedTurret == nullptr) {
					delete generatedTurret;
				}

				generatedTurret = new Turret("frame", frame->GetPositon(), frame->GetColor(), frame->GetCost());
				generatedTurret->Init();

				generatedTurret->SetScale(TURRET_SCALE);
			}
		}

		for (int i = 0; i < randomMoney.size(); i++) {
			if (randomMoney[i]->IsCoordInObject(mouseWorldPosition)) {
				randomMoney.erase(randomMoney.begin() + i);

				totalMoneyNr++;

				if (randomMoney.empty()) {
					timeCounterMoney = 0;
				}
			}
		}
	}

	if (button == GLFW_MOUSE_BUTTON_MIDDLE) {
		glm::vec2 mouseWorldPosition = GetTransformedScreenCoordToWorldCoord(mouseX, mouseY);

		for (int i = 0; i < cells.size(); i++) {
			if (cells[i]->IsCoordInObject(mouseWorldPosition) && cellsMatrix[(cells.size() - i - 1) / 3][i % 3] != 0) {
				cellsMatrix[(cells.size() - i - 1) / 3][i % 3] = 0;

				for (int j = 0; j < placedTurrets.size(); j++) {
					if (placedTurrets[j]->IsCoordInObject(mouseWorldPosition)) {
						placedTurrets.erase(placedTurrets.begin() + j);
					}
				}
			}

			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					cout << cellsMatrix[i][j] << " ";
				}

				cout << endl;
			}
		}
	}

}

void m1::Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) {
	if (button == GLFW_MOUSE_BUTTON_RIGHT) {
		glm::vec2 mouseWorldPosition = GetTransformedScreenCoordToWorldCoord(mouseX, mouseY);

		if (generatedTurret != nullptr) {
			for (int i = 0; i < cells.size(); i++) {
				if (cells[i]->IsCoordInObject(mouseWorldPosition) && cellsMatrix[(cells.size() - i - 1) / 3][i % 3] == 0 && totalMoneyNr - generatedTurret->GetCost() >= 0) {
					Turret* turret = new Turret("turret", cells[i]->GetPosition(), generatedTurret->GetColor(), generatedTurret->GetCost());
					turret->Init();

					turret->SetScale(TURRET_SCALE);

					placedTurrets.push_back(turret);

					cellsMatrix[(cells.size() - i - 1) / 3][i % 3] = 1;

					totalMoneyNr -= turret->GetCost();
				}

				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 3; j++) {
						cout << cellsMatrix[i][j] << " ";
					}

					cout << endl;
				}
			}

			delete generatedTurret;
			generatedTurret = nullptr;
		}
	}
}

void m1::Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void m1::Tema1::OnWindowResize(int width, int height)
{
}
