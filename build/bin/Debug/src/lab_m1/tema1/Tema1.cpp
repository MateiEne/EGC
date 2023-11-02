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
	cullFace = GL_BACK;
	polygonMode = GL_FILL;

	testTuret = new Turret("TestTurret");

	glEnable(GL_CULL_FACE);

	vector<VertexFormat> vertices{
		// position, color, norm
		VertexFormat(glm::vec3(0, 0, 1), glm::vec3(0, 1, 1), glm::vec3(0.2, 0.8, 0.6)),
		VertexFormat(glm::vec3(1, 0, 1), glm::vec3(0, 1, 1), glm::vec3(0.2, 0.8, 0.6)),
		VertexFormat(glm::vec3(0, 1, 1), glm::vec3(0, 1, 1), glm::vec3(0.2, 0.8, 0.6)),
		VertexFormat(glm::vec3(1, 1, 1), glm::vec3(0, 1, 1), glm::vec3(0.2, 0.8, 0.6)),
		VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0, 1, 1), glm::vec3(0.2, 0.8, 0.6)),
		VertexFormat(glm::vec3(1, 0, 0), glm::vec3(0, 1, 1), glm::vec3(0.2, 0.8, 0.6)),
		VertexFormat(glm::vec3(0, 1, 0), glm::vec3(0, 1, 1), glm::vec3(0.2, 0.8, 0.6)),
		VertexFormat(glm::vec3(1, 1, 0), glm::vec3(0, 1, 1), glm::vec3(0.2, 0.8, 0.6)),
	};

	vector<unsigned int> indices = {
		0, 1, 2,    // indices for first triangle
		1, 3, 2,    // indices for second triangle
		2, 3, 7,
		2, 7, 6,
		1, 7, 3,
		1, 5, 7,
		6, 7, 4,
		7, 5, 4,
		0, 4, 1,
		1, 4, 5,
		2, 6, 4,
		0, 2, 4,
	};

	testTuret->CreateTurret(vertices, indices);
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
	glLineWidth(3);
	glPointSize(5);
	glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

	testTuret->Render(glm::vec3(0, 0, 0), glm::vec3(0.25f));
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
