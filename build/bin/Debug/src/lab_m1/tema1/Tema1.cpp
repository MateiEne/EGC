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

	auto camera = GetSceneCamera();
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->SetOrthographic(0, 60, 0, 30, 0.01, 400);
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

	blueTurret = new Turret("blueTurret", glm::vec2(0, 0), glm::vec3(0.f, 0.f, 204 / 256.f), 2);
	blueTurret->Init();

	yellowTurret = new Turret("yellowTurret", glm::vec2(0, 0), glm::vec3(204 / 256.f, 204 / 256.f, 0.f), 2);
	yellowTurret->Init();

	purpleTurret = new Turret("purpleTurret", glm::vec2(0, 0), glm::vec3(102 / 256.f, 0.f, 204 / 256.f), 3);
	purpleTurret->Init();
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
	RenderMesh2D(base->GetDebugMesh(), shaders["VertexColor"], base->GetModelMatrix());
	RenderMesh2D(base->GetMesh(), shaders["VertexColor"], base->GetModelMatrix());

	for each (auto cell in cells) {
		RenderMesh2D(cell->GetDebugMesh(), shaders["VertexColor"], cell->GetModelMatrix());
		RenderMesh2D(cell->GetMesh(), shaders["VertexColor"], cell->GetModelMatrix());
	}
}

void Tema1::DrawHUD() {
	float turretOffset = 4.f;
	
	for (int i = 0; i < 4; i++) {
		turretFrame->SetPosition(i * (turretFrame->GetRadius() + turretOffset) + 3.f, 27);
		turretFrame->SetScale(3.8, 3.8);
		RenderMesh2D(turretFrame->GetDebugMesh(), shaders["VertexColor"], turretFrame->GetModelMatrix());
		RenderMesh2D(turretFrame->GetMesh(), shaders["VertexColor"], turretFrame->GetModelMatrix());
	}

	orangeTurret->SetPosition(3.f, 27);
	orangeTurret->SetScale(1.5f, 1.8f);
	RenderMesh2D(orangeTurret->GetDebugMesh(), shaders["VertexColor"], orangeTurret->GetModelMatrix());
	RenderMesh2D(orangeTurret->GetMesh(), shaders["VertexColor"], orangeTurret->GetModelMatrix());

	blueTurret->SetPosition(turretFrame->GetRadius() + turretOffset + 3.f, 27);
	blueTurret->SetScale(1.5f, 1.8f);
	RenderMesh2D(blueTurret->GetDebugMesh(), shaders["VertexColor"], blueTurret->GetModelMatrix());
	RenderMesh2D(blueTurret->GetMesh(), shaders["VertexColor"], blueTurret->GetModelMatrix());

	yellowTurret->SetPosition(2 * (turretFrame->GetRadius() + turretOffset) + 3.f, 27);
	yellowTurret->SetScale(1.5f, 1.8f);
	RenderMesh2D(yellowTurret->GetDebugMesh(), shaders["VertexColor"], yellowTurret->GetModelMatrix());
	RenderMesh2D(yellowTurret->GetMesh(), shaders["VertexColor"], yellowTurret->GetModelMatrix());

	purpleTurret->SetPosition(3 * (turretFrame->GetRadius() + turretOffset) + 3.f, 27);
	purpleTurret->SetScale(1.5f, 1.8f);
	RenderMesh2D(purpleTurret->GetDebugMesh(), shaders["VertexColor"], purpleTurret->GetModelMatrix());
	RenderMesh2D(purpleTurret->GetMesh(), shaders["VertexColor"], purpleTurret->GetModelMatrix());
}

void Tema1::FrameEnd() {
	DrawCoordinateSystem();
}

void m1::Tema1::OnInputUpdate(float deltaTime, int mods)
{
}

void m1::Tema1::OnKeyPress(int key, int mods)
{
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
