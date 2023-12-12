#include "lab_m1/tema2/Transform3D.h"

Transform3D::Transform3D() {
	position = glm::vec3(0);
	scale = glm::vec3(1);
	degreesOX = 0;
	degreesOY = 0;
	degreesOZ = 0;
}

Transform3D::~Transform3D() {

}

void Transform3D::SetPosition(glm::vec3 position) {
	this->position = position;
}

void Transform3D::SetPosition(float x, float y, float z) {
	SetPosition(glm::vec3(x, y, z));
}

void Transform3D::Translate(glm::vec3 translate) {
	position += translate;
}

void Transform3D::Translate(float translateX, float translateY, float translateZ) {
	Translate(glm::vec3(translateX, translateY, translateZ));
}


void Transform3D::SetScale(glm::vec3 scale) {
	this->scale = scale;
}

void Transform3D::SetScale(float scaleX, float scaleY, float scaleZ) {
	SetScale(glm::vec3(scaleX, scaleY, scaleZ));
}

void Transform3D::Scale(glm::vec3 scale) {
	this->scale *= scale;
}

void Transform3D::Scale(float scaleX, float scaleY, float scaleZ) {
	Scale(glm::vec3(scaleX, scaleY, scaleZ));
}

void Transform3D::RotateOX(float degrees) {
	degreesOX -= degrees * TO_RADIANS;
}

void Transform3D::RotateOY(float degrees) {
	//degreesOY -= T3D::degreesToRadians(degrees);
	degreesOY = degreesOY - (degrees * TO_RADIANS);
}

void Transform3D::RotateOZ(float degrees) {
	degreesOZ -= degrees * TO_RADIANS;
}

glm::mat4 Transform3D::GetModelMatrix()
{
	glm::mat4 modelMatrix = glm::mat4(1);

	modelMatrix *= T3D::Translate(position.x, position.y, position.z);
	modelMatrix *= T3D::RotateOX(degreesOX);
	modelMatrix *= T3D::RotateOY(degreesOY);
	modelMatrix *= T3D::RotateOZ(degreesOZ);
	modelMatrix *= T3D::Scale(scale.x, scale.y, scale.z);

	return modelMatrix;
}

glm::vec3 Transform3D::GetPosition() {
	return position;
}
