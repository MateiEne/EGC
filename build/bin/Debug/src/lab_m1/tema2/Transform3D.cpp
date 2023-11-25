#include "lab_m1/tema2/Transform3D.h"

Transform3D::Transform3D() {
	position = glm::vec3(0);
	scale = glm::vec3(1);
	radians = 0;
}

Transform3D::~Transform3D() {

}

void Transform3D::SetPosition(glm::vec3 position) {
	this->position = position;
}

void Transform3D::SetPosition(float x, float y, float z) {
	SetPosition(glm::vec3(x, y, z));
}

void Transform3D::SetScale(glm::vec3 scale) {
	this->scale = scale;
}

void Transform3D::SetScale(float scaleX, float scaleY, float scaleZ) {
	SetScale(glm::vec3(scaleX, scaleY, scaleZ));
}

void Transform3D::Translate(glm::vec3 translate) {
	position += translate;
}

void Transform3D::Translate(float translateX, float translateY, float translateZ) {
	Translate(glm::vec3(translateX, translateY, translateZ));
}

void Transform3D::Scale(glm::vec3 scale) {
	this->scale *= scale;
}

void Transform3D::Scale(float scaleX, float scaleY, float scaleZ) {
	Scale(glm::vec3(scaleX, scaleY, scaleZ));
}

void Transform3D::Rotate(float radians) {
	this->radians += radians;
}

glm::mat4 Transform3D::GetModelMatrix()
{
	glm::mat4 modelMatrix = glm::mat4(1);

	modelMatrix *= T3D::Translate(position.x, position.y, position.z);
	modelMatrix *= T3D::RotateOX(radians);
	modelMatrix *= T3D::RotateOY(radians);
	modelMatrix *= T3D::RotateOZ(radians);
	modelMatrix *= T3D::Scale(scale.x, scale.y, scale.z);

	return modelMatrix;
}
