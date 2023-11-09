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
	//GetCameraInput()->SetActive(false);

	InitGameScene();
	InitHUD();
}

void Tema1::InitGameScene() {
	base = new Square("base", glm::vec2(1, 8), glm::vec3(1, 0, 0));
	base->Init();
	base->Scale(glm::vec2(1.5, 15));

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			Square* cell = new Square("cell", glm::vec2(5, 2.8), GREEN_COLOR);
			cell->Init();
			float scaleFactor = 3.8;
			cell->Scale(scaleFactor, scaleFactor);
			cell->Translate(j * (2 * cell->GetRadius()) / scaleFactor, i * 2 * cell->GetRadius() / scaleFactor);

			cells.push_back(cell);
		}
	}
}

void m1::Tema1::InitHUD() {
	turretFrame = new Frame("turretFrame", glm::vec2(0, 0), glm::vec3(1, 1, 1));
	turretFrame->Init();

	projectile = new Projectile("p", glm::vec2(0, 0), GREY_COLOR);
	projectile->Init();
		
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

	InitLives();
	InitTotalMoney();
}


void m1::Tema1::InitLives() {
	float lifeOffset = 7.f;

	for (int i = 0; i < 3; i++) {
		Square* life = new Square("life", glm::vec2(0, 0), RED_COLOR);
		life->Init();
		life->SetPosition(CAMERA_ORTHO_WIDTH - lifeOffset - i * (life->GetRadius() + 4.f), 27);
		life->SetScale(2.8f, 2.8f);

		lives.insert(lives.begin(), life);
	}
}

void m1::Tema1::InitTotalMoney() {
	float totalMoneyOffset = 5.f;

	for (int i = 0; i < 10; i++) {
		Projectile* money = new Projectile("life", glm::vec2(0, 0), GREY_COLOR);
		money->Init();
		money->SetPosition(CAMERA_ORTHO_WIDTH - totalMoneyOffset - i * (money->GetRadius() + 1.f), 24.3f);
		money->SetScale(1.1f, 1.1f);

		totalMoney.insert(totalMoney.begin(), money);
	}
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
	DrawScene();
	DrawHUD();
}

void Tema1::DrawScene() {
	glm::mat4 cameraViewMatrix = GetSceneCamera()->GetViewMatrix();
	glm::mat4 cameraProjectionMatrix = GetSceneCamera()->GetProjectionMatrix();

	base->Draw(shaders["VertexColor"], cameraViewMatrix, cameraProjectionMatrix);

	for each (auto cell in cells) {
		cell->Draw(shaders["VertexColor"], cameraViewMatrix, cameraProjectionMatrix);
	}
}

void Tema1::DrawHUD() {
	float starPriceOffset = 2.f;

	glm::mat4 cameraViewMatrix = GetSceneCamera()->GetViewMatrix();
	glm::mat4 cameraProjectionMatrix = GetSceneCamera()->GetProjectionMatrix();

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

	for (int i = 0; i < lives.size(); i++) {
		lives[i]->Draw(shaders["VertexColor"], cameraViewMatrix, cameraProjectionMatrix);
	}
}

void m1::Tema1::DrawTotalMoney() {
	glm::mat4 cameraViewMatrix = GetSceneCamera()->GetViewMatrix();
	glm::mat4 cameraProjectionMatrix = GetSceneCamera()->GetProjectionMatrix();

	for each (auto money in totalMoney) {
		money->Draw(shaders["VertexColor"], cameraViewMatrix, cameraProjectionMatrix);
	}
}

void m1::Tema1::DrawStarsRandom() {

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
	if (lives.size() > 0) {
		if (key == GLFW_KEY_U) {
			lives.pop_back();
		}
	}

	if (totalMoney.size() > 0) {
		if (key == GLFW_KEY_M) {
			totalMoney.pop_back();
		}
	}

	if (key == GLFW_KEY_R) {
		cout << rand() % (3 - 1 + 1) + 1 << " ";
	}
}

void m1::Tema1::OnKeyRelease(int key, int mods)
{
}

void m1::Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
}

void m1::Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) {
	glm::vec2 mouseWorldPosition = GetTransformedScreenCoordToWorldCoord(mouseX, mouseY);

	cout << mouseWorldPosition.x << " " << mouseWorldPosition.y << endl;

	for each (auto frame in guiFrames) {
		if (frame->IsCoordInFrame(mouseWorldPosition)) {
			cout << "is in frame: " << frame->GetColor() << endl;
		}
	}
}

void m1::Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
}

void m1::Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void m1::Tema1::OnWindowResize(int width, int height)
{
}
