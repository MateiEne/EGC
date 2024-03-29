#pragma once

#include "core/gpu/mesh.h"
#include "core/gpu/shader.h"

#include "lab_m1/tema2/Transform3D.h"
#include "lab_m1/tema2/Constants.h"
#include "lab_m1/tema2/SphereCollider.h"

#include "lab_m1/tema2/SceneColliders.h"

#include <string>

using namespace std;

class Missile : public Transform3D, public SphereCollider {
public:
	Missile();
	~Missile();

	void Init(
		const string& fileLocation, 
		const string& missileFileName, 
		glm::vec3 initialPosition, 
		glm::vec3 direction, 
		glm::vec3 color
	);

	void Update(float dt);

	bool IsDead();

	glm::vec3 GetDirection();
	float GetRadius() override;
	glm::vec3 GetCenter() override;
	void TakeDamage(Collider* collider) override;

	void Draw(Shader* shader, glm::mat4 viewMatrix, glm::mat4 projectionMatrix);

private:
	float CalculateRadius();

private:
	float radius;

	Mesh* mesh;
	glm::vec3 direction;
	glm::vec3 initialPosition;

	bool isDead;

	glm::vec3 color;
};