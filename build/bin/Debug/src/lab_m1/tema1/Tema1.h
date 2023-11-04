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
		struct ViewportSpace
		{
			ViewportSpace() : x(0), y(0), width(1), height(1) {}
			ViewportSpace(int x, int y, int width, int height)
				: x(x), y(y), width(width), height(height) {}
			int x;
			int y;
			int width;
			int height;
		};

		struct LogicSpace
		{
			LogicSpace() : x(0), y(0), width(1), height(1) {}
			LogicSpace(float x, float y, float width, float height)
				: x(x), y(y), width(width), height(height) {}
			float x;
			float y;
			float width;
			float height;
		};

		Tema1();
		~Tema1();

		void Init() override;

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void DrawScene(glm::mat3 visMatrix);

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;

		// Sets the logic space and view space
		// logicSpace: { x, y, width, height }
		// viewSpace: { x, y, width, height }
		glm::mat3 VisualizationTransf2D(const LogicSpace& logicSpace, const ViewportSpace& viewSpace);
		glm::mat3 VisualizationTransf2DUnif(const LogicSpace& logicSpace, const ViewportSpace& viewSpace);

		void SetViewportArea(const ViewportSpace& viewSpace, glm::vec3 colorColor = glm::vec3(0), bool clear = true);

		Turret* testTuret;
		Enemy* enemy;
		Projectile* projectile;
		Square* square;

	protected:
		ViewportSpace viewSpace;
		LogicSpace logicSpace;
		glm::mat3 modelMatrix, visMatrix;

		GLenum polygonMode;
		GLenum cullFace;
	};
}