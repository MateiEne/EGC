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

	testTuret = new Turret("TestTurret", glm::vec3(1, 1, 0));
	testTuret->Init();

	enemy = new Enemy("E1", glm::vec3(2, 1, 0));
	enemy->Init();

	projectile = new Projectile("P1", glm::vec3(3, 1, 0));
	projectile->Init();

	square = new Square("S1", glm::vec3(4, 1, 0));
	square->Init();
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
}

void Tema1::DrawScene()
{
	modelMatrix = glm::mat3(1);
	modelMatrix *= transform2D::Translate(10, 10);
	RenderMesh2D(enemy->GetMesh(), shaders["VertexColor"], modelMatrix);
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
