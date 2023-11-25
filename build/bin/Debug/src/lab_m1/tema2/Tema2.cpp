#include "lab_m1/tema2/Tema2.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema2::Tema2() {
}


Tema2::~Tema2() {
}


void Tema2::Init() {
	polygonMode = GL_FILL;

	tank = new Tank();
	tank->Init(
		"C:\\gfx framework\\gfx-framework-master\\gfx-framework-master\\src\\lab_m1\\tema2\\assets\\Tank1",
		"base.obj",
		"turret.obj",
		"gun.obj",
		"wheel.obj"
	);
}

void Tema2::FrameStart()
{
	// Clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Tema2::Update(float deltaTimeSeconds)
{
	glLineWidth(3);
	glPointSize(5);
	glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

	// Sets the screen area where to draw
	glm::ivec2 resolution = window->GetResolution();
	glViewport(0, 0, resolution.x, resolution.y);

	glm::mat4 cameraViewMatrix = GetSceneCamera()->GetViewMatrix();
	glm::mat4 cameraProjectionMatrix = GetSceneCamera()->GetProjectionMatrix();

	tank->Draw(shaders["VertexNormal"], cameraViewMatrix, cameraProjectionMatrix);


	DrawCoordinateSystem();

	glClear(GL_DEPTH_BUFFER_BIT);


}

void Tema2::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema2::OnInputUpdate(float deltaTime, int mods) {
	if (window->KeyHold(GLFW_KEY_W)) {
		tank->MoveForward(deltaTime);
	}
	else if (window->KeyHold(GLFW_KEY_S)) {
		tank->MoveBackwards(deltaTime);
	}
	else if (window->KeyHold(GLFW_KEY_A)) {
		tank->RotateLeft(deltaTime);
	}
	else if (window->KeyHold(GLFW_KEY_D)) {
		tank->RotateRight(deltaTime);
	}
}


void Tema2::OnKeyPress(int key, int mods)
{

}


void Tema2::OnKeyRelease(int key, int mods)
{
	// Add key release event
}


void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// Add mouse move event
}


void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// Add mouse button press event
}


void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// Add mouse button release event
}


void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema2::OnWindowResize(int width, int height)
{
}
