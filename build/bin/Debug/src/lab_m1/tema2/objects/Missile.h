#pragma once

#include "core/gpu/mesh.h"
#include "core/gpu/shader.h"

#include "lab_m1/tema2/Transform3D.h"
#include "lab_m1/tema2/Constants.h"

#include <string>

using namespace std;

class Missile : public Transform3D {
public:
	Missile(glm::vec3 initialPosition, glm::vec3 direction);
	~Missile();

	void Init(
		const string& fileLocation, 
		const string& missileFileName
	);

	void Update(float dt);

	bool IsDead();

	glm::vec3 GetDirection();

	void Draw(Shader* shader, glm::mat4 viewMatrix, glm::mat4 projectionMatrix);

private:
	Mesh* mesh;
	glm::vec3 direction;
	glm::vec3 initialPosition;

	bool isDead;
};