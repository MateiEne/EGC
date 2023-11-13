#include "GUIFrame.h"

using namespace Tema1Constants;

GUIFrame::GUIFrame(const char* name, glm::vec2 position, glm::vec3 color, int cost) {
	this->position = position;
	this->color = color;

	frame = new Frame(name, position, WHITE_COLOR);
	frame->Init();

	frame->SetScale(3.8, 3.8);

	turret = new Turret(name, position, color, cost);
	turret->Init();

	turret->SetScale(TURRET_SCALE);

	for (int i = 0; i < cost; i++) {
		Projectile* star = new Projectile("Cost", glm::vec2(0, 0), GOLD_COLOR);
		star->Init();

		star->SetPosition(glm::vec2(position.x - frame->GetRadius() / 2 + i * (star->GetRadius() * 2), position.y - frame->GetRadius()));

		this->cost.push_back(star);
	}
}

GUIFrame::~GUIFrame() {
}

void GUIFrame::Draw(Shader* shader, const glm::mat4 viewMatrix, const glm::mat4 projectionMatrix) {
	frame->Draw(shader, viewMatrix, projectionMatrix);
	turret->Draw(shader, viewMatrix, projectionMatrix);

	for each (auto star in cost) {
		star->Draw(shader, viewMatrix, projectionMatrix);
	}
}

bool GUIFrame::IsCoordInFrame(glm::vec2 coord) {
	if (coord.x < (position.x + frame->GetWidth() / 2) && (coord.x > (position.x - frame->GetWidth() / 2))) {
		if (coord.y < (position.y + frame->GetHeight() / 2) && coord.y >(position.y - frame->GetHeight() / 2)) {
			return true;
		}
	}

	return false;
}

glm::vec3 GUIFrame::GetColor()
{
	return color;
}

glm::vec2 GUIFrame::GetPositon() {
	return position;
}

int GUIFrame::GetCost() {
	return turret->GetCost();
}
