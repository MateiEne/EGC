#include "lab_m1/tema1/Tema1.h"

#include <vector>
#include <iostream>

using namespace std;
using namespace m1;

Tema1::Tema1() {

}

Tema1::~Tema1() {

}

void Tema1::Init() {
	polygonMode = GL_FILL;

	orthoRight = 60;
	orthoTop = 30;

	auto camera = GetSceneCamera();
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->SetOrthographic(0, orthoRight, 0, orthoTop, 0.01, 400);
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
			Square* cell = new Square("cell", glm::vec2(5, 2.8), glm::vec3(34.0f / 256, 139.0f / 256, 34.0f / 256));
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

	orangeTurret = new Turret("orangeTurret", glm::vec2(0, 0), glm::vec3(255 / 255.f, 128 / 256.f, 0), 1);
	orangeTurret->Init();
	for (int i = 0; i < orangeTurret->GetCost(); i++) {
		Projectile* star = new Projectile("Cost", glm::vec2(0, 0), glm::vec3(192 / 256.f, 192 / 256.f, 192 / 256.f));
		star->Init();

		orangeTurretStars.push_back(star);
	}
	
	blueTurret = new Turret("blueTurret", glm::vec2(0, 0), glm::vec3(0.f, 0.f, 204 / 256.f), 2);
	blueTurret->Init();
	for (int i = 0; i < blueTurret->GetCost(); i++) {
		Projectile* star = new Projectile("Cost", glm::vec2(0, 0), glm::vec3(192 / 256.f, 192 / 256.f, 192 / 256.f));
		star->Init();

		blueTurretStars.push_back(star);
	}

	yellowTurret = new Turret("yellowTurret", glm::vec2(0, 0), glm::vec3(204 / 256.f, 204 / 256.f, 0.f), 2);
	yellowTurret->Init();
	for (int i = 0; i < yellowTurret->GetCost(); i++) {
		Projectile* star = new Projectile("Cost", glm::vec2(0, 0), glm::vec3(192 / 256.f, 192 / 256.f, 192 / 256.f));
		star->Init();

		yellowTurretStars.push_back(star);
	}

	purpleTurret = new Turret("purpleTurret", glm::vec2(0, 0), glm::vec3(102 / 256.f, 0.f, 204 / 256.f), 3);
	purpleTurret->Init();
	for (int i = 0; i < purpleTurret->GetCost(); i++) {
		Projectile* star = new Projectile("Cost", glm::vec2(0, 0), glm::vec3(192 / 256.f, 192 / 256.f, 192 / 256.f));
		star->Init();

		purpleTurretStars.push_back(star);
	}

	projectile = new Projectile("p", glm::vec2(0, 0), glm::vec3(192 / 256.f, 192 / 256.f, 192 / 256.f));
	projectile->Init();

	InitLives();
	InitTotalMoney();
}


void m1::Tema1::InitLives() {
	float lifeOffset = 7.f;

	for (int i = 0; i < 3; i++) {
		Square* life = new Square("life", glm::vec2(0, 0), glm::vec3(1, 0, 0));
		life->Init();
		life->SetPosition(orthoRight - lifeOffset - i * (life->GetRadius() + 4.f), 27);
		life->SetScale(2.8f, 2.8f);

		lives.insert(lives.begin(), life);
	}
}

void m1::Tema1::InitTotalMoney() {
	float totalMoneyOffset = 5.f;

	for (int i = 0; i < 10; i++) {
		Projectile* money = new Projectile("life", glm::vec2(0, 0), glm::vec3(192 / 256.f, 192 / 256.f, 192 / 256.f));
		money->Init();
		money->SetPosition(orthoRight - totalMoneyOffset - i * (money->GetRadius() + 1.f), 24.3f);
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

void Tema1::DrawScene()
{
	//RenderMesh2D(base->GetDebugMesh(), shaders["VertexColor"], base->GetModelMatrix());
	RenderMesh2D(base->GetMesh(), shaders["VertexColor"], base->GetModelMatrix());

	for each (auto cell in cells) {
		//RenderMesh2D(cell->GetDebugMesh(), shaders["VertexColor"], cell->GetModelMatrix());
		RenderMesh2D(cell->GetMesh(), shaders["VertexColor"], cell->GetModelMatrix());
	}
}

void Tema1::DrawHUD() {
	float starPriceOffset = 2.f;

	DrawHUDGUI(orangeTurret, 0);
	for (int i = 0; i < orangeTurretStars.size(); i++) {
		orangeTurretStars[i]->SetPosition(glm::vec2(i * (orangeTurretStars[i]->GetRadius() + .4f) + starPriceOffset, 27 - turretFrame->GetRadius()));
		orangeTurretStars[i]->SetScale(1.1f, 1.1f);
		//RenderMesh2D(prices[i]->GetDebugMesh(), shaders["VertexColor"], prices[i]->GetModelMatrix());
		RenderMesh2D(orangeTurretStars[i]->GetMesh(), shaders["VertexColor"], orangeTurretStars[i]->GetModelMatrix());
	}

	DrawHUDGUI(blueTurret, 1);
	for (int i = 0; i < blueTurretStars.size(); i++) {
		blueTurretStars[i]->SetPosition(glm::vec2(i * (blueTurretStars[i]->GetRadius() + .4f) + 4 + turretFrame->GetRadius() + starPriceOffset, 27 - turretFrame->GetRadius()));
		blueTurretStars[i]->SetScale(1.1f, 1.1f);
		//RenderMesh2D(prices[i]->GetDebugMesh(), shaders["VertexColor"], prices[i]->GetModelMatrix());
		RenderMesh2D(blueTurretStars[i]->GetMesh(), shaders["VertexColor"], blueTurretStars[i]->GetModelMatrix());
	}

	DrawHUDGUI(yellowTurret, 2);
	for (int i = 0; i < yellowTurretStars.size(); i++) {
		yellowTurretStars[i]->SetPosition(glm::vec2(i * (yellowTurretStars[i]->GetRadius() + .4f) + 2 * (4 + turretFrame->GetRadius()) + starPriceOffset, 27 - turretFrame->GetRadius()));
		yellowTurretStars[i]->SetScale(1.1f, 1.1f);
		//RenderMesh2D(prices[i]->GetDebugMesh(), shaders["VertexColor"], prices[i]->GetModelMatrix());
		RenderMesh2D(yellowTurretStars[i]->GetMesh(), shaders["VertexColor"], yellowTurretStars[i]->GetModelMatrix());
	}

	DrawHUDGUI(purpleTurret, 3);
	for (int i = 0; i < purpleTurretStars.size(); i++) {
		purpleTurretStars[i]->SetPosition(glm::vec2(i * (purpleTurretStars[i]->GetRadius() + .4f) + 3 * (4 + turretFrame->GetRadius()) + starPriceOffset, 27 - turretFrame->GetRadius()));
		purpleTurretStars[i]->SetScale(1.1f, 1.1f);
		//RenderMesh2D(prices[i]->GetDebugMesh(), shaders["VertexColor"], prices[i]->GetModelMatrix());
		RenderMesh2D(purpleTurretStars[i]->GetMesh(), shaders["VertexColor"], purpleTurretStars[i]->GetModelMatrix());
	}

	DrawLives();
	DrawTotalMoney();
}

void m1::Tema1::DrawHUDGUI(Turret* turret, int factor) {
	float turretFrameOffset = 4.f;

	for (int i = 0; i < 4; i++) {
		turretFrame->SetPosition(i * (turretFrame->GetRadius() + turretFrameOffset) + 3.f, 27);
		turretFrame->SetScale(3.8, 3.8);
		//RenderMesh2D(turretFrame->GetDebugMesh(), shaders["VertexColor"], turretFrame->GetModelMatrix());
		RenderMesh2D(turretFrame->GetMesh(), shaders["VertexColor"], turretFrame->GetModelMatrix());
	}

	turret->SetPosition(factor * (turretFrame->GetRadius() + turretFrameOffset) + 3.f, 27);
	turret->SetScale(1.5f, 1.8f);
	//RenderMesh2D(turret->GetDebugMesh(), shaders["VertexColor"], turret->GetModelMatrix());
	RenderMesh2D(turret->GetMesh(), shaders["VertexColor"], turret->GetModelMatrix());
}

void m1::Tema1::DrawLives() {
	for (int i = 0; i < lives.size(); i++) {
		//RenderMesh2D(lives[i]->GetDebugMesh(), shaders["VertexColor"], lives[i]->GetModelMatrix());
		RenderMesh2D(lives[i]->GetMesh(), shaders["VertexColor"], lives[i]->GetModelMatrix());
	}
}

void m1::Tema1::DrawTotalMoney() {
	for each (auto money in totalMoney) {
		//RenderMesh2D(money->GetDebugMesh(), shaders["VertexColor"], money->GetModelMatrix());
		RenderMesh2D(money->GetMesh(), shaders["VertexColor"], money->GetModelMatrix());
	}
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
}

void m1::Tema1::OnKeyRelease(int key, int mods)
{
}

void m1::Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
}

void m1::Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
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
