#pragma once

#include "lab_m1/tema1/Constants.h"

#include "components/simple_scene.h"
#include "lab_m1/lab3/transform2D.h"

#include "lab_m1/tema1/objects/Turret.h"
#include "lab_m1/tema1/objects/Enemy.h"
#include "lab_m1/tema1/objects/Projectile.h"
#include "lab_m1/tema1/objects/Square.h"
#include "lab_m1/tema1/objects/Frame.h"
#include "lab_m1/tema1/objects/GUIFrame.h"

#include <vector>
#include <iostream>

using namespace std;
using namespace Tema1Constants;


namespace m1 {
	class Tema1 : public gfxc::SimpleScene {
	public:
		Tema1();
		~Tema1();

		void Init() override;

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void InitGameScene();
		void InitHUD();
		void InitLives();
		void InitRandomMoney();
		void InitRandomEnemies();

		void DrawScene();
		void DrawHUD();
		void DrawHUDGUI(Turret* turret, int factor);
		void DrawLives();
		void DrawTotalMoney();
		void DrawRandomMoney();
		void DrawEnemies();

		void UpdateEnemies(float deltaTime);

		void UpdateTimeCunterMoney(float deltaTime);
		void UpdateTimeCounterEnemies(float deltaTime);

		glm::vec2 GetTransformedScreenCoordToWorldCoord(int screenX, int screenY);

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;

	private:
		Square* base;
		vector<Square*> cells;

		Frame* turretFrame;
		
		vector<Projectile*> randomMoney;

		Turret* generatedTurret;

		vector<Square*> lives;

		vector<GUIFrame*> guiFrames;
		vector<Turret*> placedTurrets;

		GLenum polygonMode;
		GLenum cullFace;

		glm::mat3 cellsMatrix;

		float timeCounterMoney;
		float timeToSpawnRandomMoney;

		Projectile* money;
		int totalMoneyNr;

		float totalMoneyPosX;
		float totalMoneyPosY;

		vector<Enemy*> enemies;
		vector<glm::vec2> enemyPositions;
		float timeCounterEnemies;
		float timeToSpawnEnemies;
	};
}