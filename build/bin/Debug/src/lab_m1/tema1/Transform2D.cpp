#include "lab_m1/tema1/Transform2D.h"

Transform2D::Transform2D() {
	modelMatrix = glm::mat3(1);
}

Transform2D::~Transform2D() {
}

void Transform2D::Translate(glm::vec2 translate) {
	modelMatrix *= glm::transpose(
		glm::mat3(
			1, 0, translate.x,
			0, 1, translate.y,
			0, 0, 1
		)
	);
}

void Transform2D::Scale(glm::vec2 scale) {
	modelMatrix *= glm::transpose(
		glm::mat3(
			scale.x, 0, 0,
			0, scale.y, 0,
			0, 0, 1
		)
	);
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

glm::mat3 Transform2D::GetModelMatrix() {
	return modelMatrix;
}