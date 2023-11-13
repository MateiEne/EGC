#include "lab_m1/tema1/Transform2D.h"

Transform2D::Transform2D() {
	modelMatrix = glm::mat3(1);
	position = glm::vec2(0);
	scale = glm::vec2(1);
}

Transform2D::~Transform2D() {
}

void Transform2D::SetPosition(float x, float y) {
	SetPosition(glm::vec2(x, y));
}

void Transform2D::SetScale(glm::vec2 scale) {
	modelMatrix = glm::transpose(
		glm::mat3(
			scale.x, 0, position.x,
			0, scale.y, position.y,
			0, 0, 1
		)
	);

	this->scale = scale;
}

void Transform2D::SetScale(float scaleX, float scaleY) {
	SetScale(glm::vec2(scaleX, scaleY));
}

void Transform2D::SetPosition(glm::vec2 position) {
	modelMatrix = glm::transpose(
		glm::mat3(
			scale.x, 0, position.x,
			0, scale.y, position.y,
			0, 0, 1
		)
	);

	this->position = position;
}

void Transform2D::Translate(float translateX, float translateY) {
	Translate(glm::vec2(translateX, translateY));
}

void Transform2D::Scale(float scaleX, float scaleY) {
	Scale(glm::vec2(scaleX, scaleY));
}

void Transform2D::Translate(glm::vec2 translate) {
	modelMatrix *= glm::transpose(
		glm::mat3(
			1, 0, translate.x,
			0, 1, translate.y,
			0, 0, 1
		)
	);

	position = GetPositionFromModelMatrix();
}

void Transform2D::Scale(glm::vec2 scale) {
	modelMatrix *= glm::transpose(
		glm::mat3(
			scale.x, 0, 0,
			0, scale.y, 0,
			0, 0, 1
		)
	);

	this->scale = GetScaleFromModelMatrix();
}

void Transform2D::Rotate(float radians) {
	modelMatrix *= glm::transpose(
		glm::mat3(
			cos(radians), -sin(radians), 0,
			sin(radians), cos(radians), 0,
			0, 0, 1
		)
	);
}

void Transform2D::ResetModelMatrix() {
	modelMatrix = glm::mat3(1);
}

glm::mat3 Transform2D::GetModelMatrix() {
	return modelMatrix;
}

glm::vec2 Transform2D::GetPositionFromModelMatrix() {
	return glm::vec2(modelMatrix[2][0], modelMatrix[2][1]);
}

glm::vec2 Transform2D::GetScaleFromModelMatrix()
{
	return glm::vec2(modelMatrix[0][0], modelMatrix[1][1]);
}
