#pragma once

#include "lab_m1/tema1/Constants.h"

#include "lab_m1/tema1/objects/Projectile.h"
#include "lab_m1/tema1/objects/Frame.h"
#include "lab_m1/tema1/objects/Turret.h"

using namespace Tema1Constants;

class GUIFrame {
public:
	GUIFrame(const char* name, glm::vec2 position, glm::vec3 color, int cost);
	~GUIFrame();

	void Draw(Shader* shader, const glm::mat4 viewMatrix, const glm::mat4 projectionMatrix);
	
	bool IsCoordInFrame(glm::vec2 coord);

	glm::vec3 GetColor();

private:
	Frame* frame;
	Turret* turret;
	
	vector<Projectile*> cost;

	glm::vec3 color;
	glm::vec2 position;
};