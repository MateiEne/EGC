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
		const string& wheelFileName
	);

	void Update(float dt);

	void MoveForward(float dt);
	void MoveBackwards(float dt);
	void RotateRight(float dt);
	void RotateLeft(float dt);

	void Fire();

	void Draw(Shader* shader, glm::mat4 viewMatrix, glm::mat4 projectionMatrix);

private:
	glm::vec3 GetGunHeadPosition();
	glm::vec3 GetDirection();

private:
	void DrawPart(Mesh* mesh, Shader* shader, glm::vec3 translation);

	Mesh* baseMesh;
	Mesh* turretMesh;
	Mesh* gunMesh;
	Mesh* wheelMesh;

	vector<Missile*> missiles;
};