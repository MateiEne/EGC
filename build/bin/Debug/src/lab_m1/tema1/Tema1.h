#pragma once

//#include "lab_m1/tema1/game_components/game_scene.h"
#include "components/simple_scene.h"
#include "lab_m1/lab3/transform2D.h"

#include "lab_m1/tema1/objects/Turret.h"
#include "lab_m1/tema1/objects/Enemy.h"
#include "lab_m1/tema1/objects/Projectile.h"
#include "lab_m1/tema1/objects/Square.h"

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

		void DrawScene();
		void InitGameScene();

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

		GLenum polygonMode;
		GLenum cullFace;
	};
}