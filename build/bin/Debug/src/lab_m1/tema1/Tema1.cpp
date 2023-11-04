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
	camera->Update();
	//GetCameraInput()->SetActive(false);

	logicSpace.x = 0;       // logic x
	logicSpace.y = 0;       // logic y
	logicSpace.width = 8;   // logic width
	logicSpace.height = 8;  // logic height

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
	glLineWidth(3);
	glPointSize(5);
	glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

	glm::ivec2 resolution = window->GetResolution();

	// Sets the screen area where to draw
	viewSpace = ViewportSpace(0, 0, resolution.x, resolution.y);
	SetViewportArea(viewSpace, glm::vec3(0), true);


	// Compute the 2D visualization matrix
	visMatrix = glm::mat3(1);
	visMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);
	DrawScene(visMatrix);
}

void Tema1::DrawScene(glm::mat3 visMatrix)
{
	modelMatrix = visMatrix * transform2D::Translate(0, 0);
	RenderMesh2D(square->GetMesh(), shaders["VertexColor"], modelMatrix);
	//RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

	//modelMatrix = visMatrix * transform2D::Translate(0, 10);
	//RenderMesh2D(enemy->GetMesh(), shaders["VertexColor"], modelMatrix);

	//modelMatrix = visMatrix * transform2D::Translate(1.5, 1.5);
	//RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

	//modelMatrix = visMatrix * transform2D::Translate(0, 3);
	//RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

	//modelMatrix = visMatrix * transform2D::Translate(3, 3);
	//RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);
}

void Tema1::FrameEnd() {
	DrawCoordinateSystem();
}

// 2D visualization matrix
glm::mat3 Tema1::VisualizationTransf2D(const LogicSpace& logicSpace, const ViewportSpace& viewSpace)
{
	float sx, sy, tx, ty;
	sx = viewSpace.width / logicSpace.width;
	sy = viewSpace.height / logicSpace.height;
	tx = viewSpace.x - sx * logicSpace.x;
	ty = viewSpace.y - sy * logicSpace.y;

	return glm::transpose(glm::mat3(
		sx, 0.0f, tx,
		0.0f, sy, ty,
		0.0f, 0.0f, 1.0f));
}


// Uniform 2D visualization matrix (same scale factor on x and y axes)
glm::mat3 Tema1::VisualizationTransf2DUnif(const LogicSpace& logicSpace, const ViewportSpace& viewSpace)
{
	float sx, sy, tx, ty, smin;
	sx = viewSpace.width / logicSpace.width;
	sy = viewSpace.height / logicSpace.height;
	if (sx < sy)
		smin = sx;
	else
		smin = sy;
	//tx = viewSpace.x - smin * logicSpace.x + (viewSpace.width - smin * logicSpace.width) / 2;
	//ty = viewSpace.y - smin * logicSpace.y + (viewSpace.height - smin * logicSpace.height) / 2;

	float tsx, tsy;

	tsx = (viewSpace.width - viewSpace.x - smin * (logicSpace.width - logicSpace.x)) / 2;
	tsy = (viewSpace.height - viewSpace.y - smin * (logicSpace.height - logicSpace.y)) / 2;

	return glm::transpose(glm::mat3(
		smin, 0.0f, tsx,
		0.0f, smin, tsy,
		0.0f, 0.0f, 1.0f));
}


void Tema1::SetViewportArea(const ViewportSpace& viewSpace, glm::vec3 colorColor, bool clear)
{
	glViewport(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

	glEnable(GL_SCISSOR_TEST);
	glScissor(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

	// Clears the color buffer (using the previously set color) and depth buffer
	glClearColor(colorColor.r, colorColor.g, colorColor.b, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_SCISSOR_TEST);

	GetSceneCamera()->SetOrthographic((float)viewSpace.x, (float)(viewSpace.x + viewSpace.width), (float)viewSpace.y, (float)(viewSpace.y + viewSpace.height), 0.1f, 400);
	GetSceneCamera()->Update();
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
