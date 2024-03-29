#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "core/gpu/mesh.h"
#include "core/gpu/shader.h"
#include "components/camera.h"

#include "lab_m1/tema2/Transform3D.h"
#include "lab_m1/tema2/Constants.h"
#include "lab_m1/tema2/GameCamera.h"
#include "lab_m1/tema2/objects/Missile.h"
#include "lab_m1/tema2/objects/Building.h"
#include "lab_m1/tema2/SphereCollider.h"

#include "lab_m1/tema2/SceneColliders.h"

using namespace std;

class Tank : public Transform3D, public SphereCollider {
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
		glm::vec3 wheelColor,
		glm::vec3 baseOffset,
		glm::vec3 turretOffset,
		glm::vec3 gunOffset,
		glm::vec3 rightWheelOffset,
		glm::vec3 leftWheelOffset,
		int maxHp
	);

	void Update(float dt);

	void MoveForward(float dt);
	void MoveBackwards(float dt);
	void RotateRight(float dt);
	void RotateLeft(float dt);

	void Fire();

	glm::vec3 GetDirection();
	glm::vec3 GetUpDirection();

	glm::vec3 GetCenter() override;
	float GetRadius() override;

	void TakeDamage(Collider* collider) override;

	float GetHeight();

	void Draw(unordered_map<std::string, Shader*> shaders, glm::mat4 viewMatrix, glm::mat4 projectionMatrix);
	void DrawDebug(unordered_map<std::string, Shader*> shaders, glm::mat4 viewMatrix, glm::mat4 projectionMatrix);

protected:
	float GetBaseRadius();

	glm::vec3 GetGunHeadPosition();
	glm::vec3 GetLowestPoint();

	void DrawPart(Mesh* mesh, Shader* shader, glm::vec3 translation, glm::vec3 color);

protected:
	int hp;
	int maxHp;

	Mesh* baseMesh;
	Mesh* turretMesh;
	Mesh* gunMesh;
	Mesh* wheelMesh;

	vector<Missile*> missiles;

	float radius;

	glm::vec3 baseColor;
	glm::vec3 turretColor;
	glm::vec3 gunColor;
	glm::vec3 wheelColor;

	glm::vec3 baseOffset;
	glm::vec3 turretOffset;
	glm::vec3 gunOffset;
	glm::vec3 rightWheelOffset;
	glm::vec3 leftWheelOffset;

	string fileLocation;
};