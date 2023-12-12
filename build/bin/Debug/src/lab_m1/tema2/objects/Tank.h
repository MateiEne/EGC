#pragma once

#include <iostream>
#include <string>
#include <map>
#include <vector>

#include "core/gpu/mesh.h"
#include "core/gpu/shader.h"
#include "components/camera.h"

#include "lab_m1/tema2/Transform3D.h"
#include "lab_m1/tema2/Constants.h"
#include "lab_m1/tema2/GameCamera.h"
#include "lab_m1/tema2/objects/Missile.h"
#include "lab_m1/tema2/objects/Building.h"

using namespace std;

class Tank : public Transform3D {
public:
	Tank();
	~Tank();

	void Init(
		const string& fileLocation,
		const string& baseFileName, 
		const string& turretFileName, 
		const string& gunFileName, 
		const string& wheelFileName,
		glm::vec3 baseColor,
		glm::vec3 turretColor,
		glm::vec3 gunColor,
		glm::vec3 wheelColor
	);

	void Update(float dt);

	void MoveForward(float dt);
	void MoveBackwards(float dt);
	void RotateRight(float dt);
	void RotateLeft(float dt);

	void Fire();

	glm::vec3 GetDirection();
	glm::vec3 GetUpDirection();

	float GetHeight();
	float GetBaseRadius();

	bool IsInCollisionWithTank(Tank* tank);
	bool IsInCollisionWithBuilding(Building* building);

	void Draw(Shader* shader, glm::mat4 viewMatrix, glm::mat4 projectionMatrix);

private:
	glm::vec3 GetGunHeadPosition();

private:
	void DrawPart(Mesh* mesh, Shader* shader, glm::vec3 translation, glm::vec3 color);

	Mesh* baseMesh;
	Mesh* turretMesh;
	Mesh* gunMesh;
	Mesh* wheelMesh;

	vector<Missile*> missiles;

	glm::vec3 baseColor;
	glm::vec3 turretColor;
	glm::vec3 gunColor;
	glm::vec3 wheelColor;
};