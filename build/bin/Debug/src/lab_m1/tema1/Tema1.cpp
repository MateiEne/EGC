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

	frame = new Frame("frame", glm::vec2(20, 20), glm::vec3(1, 0, 0));
	frame->Init();
	frame->SetScale(3.8, 3.8);
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
	RenderMesh2D(base->GetDebugMesh(), shaders["VertexColor"], base->GetModelMatrix());
	RenderMesh2D(base->GetMesh(), shaders["VertexColor"], base->GetModelMatrix());

	for each (auto cell in cells) {
		RenderMesh2D(cell->GetDebugMesh(), shaders["VertexColor"], cell->GetModelMatrix());
		RenderMesh2D(cell->GetMesh(), shaders["VertexColor"], cell->GetModelMatrix());
	}

	RenderMesh2D(frame->GetMesh(), shaders["VertexColor"], frame->GetModelMatrix());
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
