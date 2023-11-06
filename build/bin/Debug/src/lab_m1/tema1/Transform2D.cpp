#include "Transform2D.h"

Transform2D::Transform2D()
{
	modelMatrix = glm::mat3(1);
}

Transform2D::~Transform2D()
{
}

void Transform2D::setPosition(glm::vec2 position)
{
	modelMatrix *= Translate(position);
}

glm::mat3 Transform2D::Translate(glm::vec2 translate)
{
	return glm::transpose(
		glm::mat3(
			1, 0, translate.x,
			0, 1, translate.y,
			0, 0, 1
		)
	);
}

glm::mat3 Transform2D::Scale(glm::vec2 scale)
{
	return glm::transpose(
		glm::mat3(
			scale.x, 0, 0,
			0, scale.y, 0,
			0, 0, 1
		)
	);
}

glm::mat3 Transform2D::Rotate(float radians)
{
	return glm::transpose(
		glm::mat3(
			cos(radians), -sin(radians), 0,
			sin(radians), cos(radians), 0,
			0, 0, 1
		)
	);
}
