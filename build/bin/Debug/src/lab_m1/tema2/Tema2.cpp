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

	camera = new GameCamera3P(5, 20);
	camera->SetPerspective(60, window->props.aspectRatio, 0.01, 200.f);

	Shader* shader = new Shader("TemaShaders");
	shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
	shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
	shader->CreateAndLink();
	shaders[shader->GetName()] = shader;

	tank = new Tank();
	tank->Init(
		CST::TANK_ASSETS_FILE_LOCATION,
		"base.obj",
		"turret.obj",
		"gun.obj",
		"wheel.obj",
		CST::COLORS.at("dark_green"),
		CST::COLORS.at("green"),
		CST::COLORS.at("light_green"),
		CST::COLORS.at("light_green")
	);

	ground = new Ground();
	ground->Init(CST::GROUND_ASSETS_FILE_LOCATION, "ground.obj", CST::COLORS.at("grey"));
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

	tank->Update(deltaTimeSeconds);
	camera->LookAtTarget(tank->GetPosition(), tank->GetDirection(), tank->GetUpDirection());

	glm::mat4 cameraViewMatrix = camera->GetViewMatrix();
	glm::mat4 cameraProjectionMatrix = camera->GetProjectionMatrix();
	
	ground->Draw(shaders["TemaShaders"], cameraViewMatrix, cameraProjectionMatrix);
	tank->Draw(shaders["TemaShaders"], cameraViewMatrix, cameraProjectionMatrix);

	DrawCoordinateSystem(cameraViewMatrix, cameraProjectionMatrix);

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

	if (window->KeyHold(GLFW_KEY_Z)) {
		camera->SetDistanceToTarget(camera->GetDistanceToTarget() + 0.5);
	}
	if (window->KeyHold(GLFW_KEY_X)) {
		camera->SetDistanceToTarget(camera->GetDistanceToTarget() - 0.5);
	}
	if (window->KeyHold(GLFW_KEY_F)) {
		camera->SetTargetAngle(camera->GetTargetAngle() + 0.5);
	}
	if (window->KeyHold(GLFW_KEY_V)) {
		camera->SetTargetAngle(camera->GetTargetAngle() - 0.5);
	}
}


void Tema2::OnKeyPress(int key, int mods) {
	if (key == GLFW_KEY_SPACE) {
		tank->Fire();
	}
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
