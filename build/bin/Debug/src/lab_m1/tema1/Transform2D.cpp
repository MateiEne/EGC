#include "lab_m1/tema1/Transform2D.h"

Transform2D::Transform2D() {
	position = glm::vec2(0);
	scale = glm::vec2(1);
	radians = 0;
}

Transform2D::~Transform2D() {
}

void Transform2D::SetPosition(float x, float y) {
	SetPosition(glm::vec2(x, y));
}

void Transform2D::SetPosition(glm::vec2 position) {
	this->position = position;
}

void Transform2D::SetScale(glm::vec2 scale) {
	this->scale = scale;
}

void Transform2D::SetScale(float scaleX, float scaleY) {
	SetScale(glm::vec2(scaleX, scaleY));
}
void Transform2D::Translate(float translateX, float translateY) {
	Translate(glm::vec2(translateX, translateY));
}

void Transform2D::Translate(glm::vec2 translate) {
	position += translate;
}

void Transform2D::Scale(glm::vec2 scale) {
	this->scale *= scale;
}

void Transform2D::Scale(float scaleX, float scaleY) {
	Scale(glm::vec2(scaleX, scaleY));
}

void Transform2D::Rotate(float radians) {
	this->radians += radians;
}

glm::mat3 Transform2D::GetModelMatrix() {
	glm::mat3 modelMatrix = glm::mat3(1);
	
	modelMatrix *= T2D::Translate(position.x, position.y);
	modelMatrix *= T2D::Rotate(radians);
	modelMatrix *= T2D::Scale(scale.x, scale.y);

	return modelMatrix;
}
