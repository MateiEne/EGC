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

	Shader* tankShader = new Shader("TankShaders");
	tankShader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "shaders", "TankVertexShader.glsl"), GL_VERTEX_SHADER);
	tankShader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
	tankShader->CreateAndLink();
	shaders[tankShader->GetName()] = tankShader;

	ground = new Ground();
	ground->Init(CST::GROUND_ASSETS_FILE_LOCATION, "ground.obj", CST::COLORS.at("grey"));

	tank = new Tank();
	tank->Init(
		CST::TANK3_ASSETS_FILE_LOCATION,
		"Base.obj",
		"Turret.obj",
		"Gun.obj",
		"Wheel.obj",
		CST::COLORS.at("dark_green"),
		CST::COLORS.at("green"),
		CST::COLORS.at("light_green"),
		CST::COLORS.at("light_green"),
		CST::TANK3_BASE_INITIAL_POS,
		CST::TANK3_TURRET_INITIAL_POS,
		CST::TANK3_GUN_INITIAL_POS,
		CST::TANK3_RIGHT_WHEEL_INITIAL_POS,
		CST::TANK3_LEFT_WHEEL_INITIAL_POS, 
		3
	);
	tank->Translate(0, ground->GetHeight() / 2, 0);
	SceneColliders::GetInstance().AddCollider(tank);

	testTank = new Tank();
	testTank->Init(
		CST::TANK3_ASSETS_FILE_LOCATION,
		"Base.obj",
		"Turret.obj",
		"Gun.obj",
		"Wheel.obj",
		CST::COLORS.at("dark_green"),
		CST::COLORS.at("green"),
		CST::COLORS.at("light_green"),
		CST::COLORS.at("light_green"),
		CST::TANK3_BASE_INITIAL_POS,
		CST::TANK3_TURRET_INITIAL_POS,
		CST::TANK3_GUN_INITIAL_POS,
		CST::TANK3_RIGHT_WHEEL_INITIAL_POS,
		CST::TANK3_LEFT_WHEEL_INITIAL_POS, 
		3
	);
	testTank->Translate(5, ground->GetHeight() / 2, 0);
	SceneColliders::GetInstance().AddCollider(testTank);

	idiot = new IdiotTank(glm::vec3(-100, 0, 100), glm::vec3(100, 0, -100));
	idiot->Init(
		CST::TANK2_ASSETS_FILE_LOCATION,
		"Base.obj",
		"Turret.obj",
		"Gun.obj",
		"Wheel.obj",
		CST::COLORS.at("dark_green"),
		CST::COLORS.at("green"),
		CST::COLORS.at("light_green"),
		CST::COLORS.at("light_green"),
		CST::TANK2_BASE_INITIAL_POS,
		CST::TANK2_TURRET_INITIAL_POS,
		CST::TANK2_GUN_INITIAL_POS,
		CST::TANK2_RIGHT_WHEEL_INITIAL_POS,
		CST::TANK2_LEFT_WHEEL_INITIAL_POS,
		3
	);
	idiot->Translate(-5, ground->GetHeight() / 2, -17);
	SceneColliders::GetInstance().AddCollider(idiot);

	definedPathTank = new DefinedPathTank(glm::vec3(20, 0, -45), glm::vec3(-20, 0, 45));
	definedPathTank->Init(
		CST::TANK1_ASSETS_FILE_LOCATION,
		"Base.obj",
		"Turret.obj",
		"Gun.obj",
		"Wheel.obj",
		CST::COLORS.at("dark_green"),
		CST::COLORS.at("green"),
		CST::COLORS.at("light_green"),
		CST::COLORS.at("light_green"),
		CST::TANK1_BASE_INITIAL_POS,
		CST::TANK1_TURRET_INITIAL_POS,
		CST::TANK1_GUN_INITIAL_POS,
		CST::TANK1_RIGHT_WHEEL_INITIAL_POS,
		CST::TANK1_LEFT_WHEEL_INITIAL_POS,
		3
	);
	definedPathTank->Translate(-5, ground->GetHeight() / 2, -5);
	SceneColliders::GetInstance().AddCollider(definedPathTank);


	for (int i = 0; i < 10; i++) {
		Building* building = new Building();
		building->Init(CST::BUILDING_ASSETS_FILE_LOCATION, "building.obj", CST::COLORS.at("light_blue"));

		cout << "building " << i << "with width: " << building->GetWidth() << endl;
		cout << "building " << i << "with length: " << building->GetLength() << endl;
		cout << "building " << i << "with height: " << building->GetHeight() << endl;

		float x = -50 + rand() % 101;
		float z = -50 + rand() % 101;

		float scaleX = rand() % 5 + 2;
		float scaleY = rand() % 15 + 5;
		float scaleZ = rand() % 5 + 2;

		building->SetScale(scaleX, scaleY, scaleZ);
		building->SetPosition(x, 1, z);

		if (building->IsInCollision(tank) || building->IsInCollision(testTank)) {
			i--;

			continue;
		}


		cout << "building " << i << "with width: " << building->GetWidth() << "after scaling z with: " << scaleZ << endl;
		cout << "building " << i << "with length: " << building->GetLength() << "after scaling x with: " << scaleX << endl;
		cout << "building " << i << "with height: " << building->GetHeight() << "after scaling y with: " << scaleY << endl;

		buildings.push_back(building);
		
		SceneColliders::GetInstance().AddCollider(building);
	}

	time = 0;
}

void Tema2::FrameStart()
{
	// Clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Tema2::Update(float deltaTimeSeconds)
{
	if (time >= CST::END_TIME) {
		cout << "================== GAME ENDED ==========================" << endl;

		return;
	}

	time += deltaTimeSeconds;

	glLineWidth(3);
	glPointSize(5);
	glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

	// Sets the screen area where to draw
	glm::ivec2 resolution = window->GetResolution();
	glViewport(0, 0, resolution.x, resolution.y);

	SceneColliders::GetInstance().CheckCollisions();

	tank->Update(deltaTimeSeconds);
	camera->LookAtTarget(tank->GetPosition(), tank->GetDirection(), tank->GetUpDirection());

	idiot->Update(deltaTimeSeconds);
	definedPathTank->Update(deltaTimeSeconds);

	glm::mat4 cameraViewMatrix = camera->GetViewMatrix();
	glm::mat4 cameraProjectionMatrix = camera->GetProjectionMatrix();

	ground->Draw(shaders["TemaShaders"], cameraViewMatrix, cameraProjectionMatrix);
	tank->Draw(shaders, cameraViewMatrix, cameraProjectionMatrix);
	testTank->Draw(shaders, cameraViewMatrix, cameraProjectionMatrix);
	idiot->Draw(shaders, cameraViewMatrix, cameraProjectionMatrix);
	definedPathTank->Draw(shaders, cameraViewMatrix, cameraProjectionMatrix);

	//tank->DrawDebug(shaders["TemaShaders"], cameraViewMatrix, cameraProjectionMatrix);
	//testTank->DrawDebug(shaders["TemaShaders"], cameraViewMatrix, cameraProjectionMatrix);

	for each (auto building in buildings) {
		building->Draw(shaders["TemaShaders"], cameraViewMatrix, cameraProjectionMatrix);
	}

	//DrawCoordinateSystem(cameraViewMatrix, cameraProjectionMatrix
	
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
		if (tank->IsInCollision(testTank)) {
			glm::vec3 dif = (testTank->GetPosition() - tank->GetPosition());
			float overlap = tank->GetRadius() + testTank->GetRadius()
				- sqrt(pow((tank->GetPosition().x - testTank->GetPosition().x), 2)
					+ pow((tank->GetPosition().y - testTank->GetPosition().y), 2)
					+ pow((tank->GetPosition().z - testTank->GetPosition().z), 2));

			if (overlap < CST::COLLISION_OVERLAP_EPS) {
				overlap = CST::COLLISION_OVERLAP_EPS;
			}

			glm::vec3 direction = overlap * glm::normalize(dif);
			


			cout << overlap << endl;

			tank->Translate(direction * -0.5f);
			testTank->Translate(direction * 0.5f);
		}
		else {
			tank->MoveForward(deltaTime);
		}


		for each (auto building in buildings) {
			if (tank->IsInCollision(building)) {
				tank->MoveBackwards(deltaTime);
			}
		}
	}
	else if (window->KeyHold(GLFW_KEY_S)) {
		if (tank->IsInCollision(testTank)) {
			glm::vec3 dif = (testTank->GetPosition() - tank->GetPosition());
			float overlap = tank->GetRadius() + testTank->GetRadius()
				- sqrt(pow((tank->GetPosition().x - testTank->GetPosition().x), 2)
					+ pow((tank->GetPosition().y - testTank->GetPosition().y), 2)
					+ pow((tank->GetPosition().z - testTank->GetPosition().z), 2));
			glm::vec3 direction = overlap * glm::normalize(dif);

			cout << overlap << endl;

			tank->Translate(direction * -0.5f);
			testTank->Translate(direction * 0.5f);
		}
		else {
			tank->MoveBackwards(deltaTime);
		}

		for each (auto building in buildings) {
			if (tank->IsInCollision(building)) {
				tank->MoveForward(deltaTime);
			}
		}
	}
	else if (window->KeyHold(GLFW_KEY_A)) {
		if (tank->IsInCollision(testTank)) {
			glm::vec3 dif = (testTank->GetPosition() - tank->GetPosition());
			float overlap = tank->GetRadius() + testTank->GetRadius()
				- sqrt(pow((tank->GetPosition().x - testTank->GetPosition().x), 2)
					+ pow((tank->GetPosition().y - testTank->GetPosition().y), 2)
					+ pow((tank->GetPosition().z - testTank->GetPosition().z), 2));
			glm::vec3 direction = overlap * glm::normalize(dif);

			cout << overlap << endl;

			tank->Translate(direction * -0.5f);
			testTank->Translate(direction * 0.5f);
		}
		else {
			tank->RotateLeft(deltaTime);
		}

		for each (auto building in buildings) {
			if (tank->IsInCollision(building)) {
				tank->RotateRight(deltaTime);
			}
		}
	}
	else if (window->KeyHold(GLFW_KEY_D)) {
		if (tank->IsInCollision(testTank)) {
			glm::vec3 dif = (testTank->GetPosition() - tank->GetPosition());
			float overlap = tank->GetRadius() + testTank->GetRadius()
				- sqrt(pow((tank->GetPosition().x - testTank->GetPosition().x), 2)
					+ pow((tank->GetPosition().y - testTank->GetPosition().y), 2)
					+ pow((tank->GetPosition().z - testTank->GetPosition().z), 2));
			glm::vec3 direction = overlap * glm::normalize(dif);

			tank->Translate(direction * -0.5f);
			testTank->Translate(direction * 0.5f);
		}
		else {
			tank->RotateRight(deltaTime);
		}

		for each (auto building in buildings) {
			if (tank->IsInCollision(building)) {
				tank->RotateLeft(deltaTime);
			}
		}
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
