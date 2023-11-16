#pragma once

#include "lab_m1/tema1/objects/Object_2D.h"
#include "lab_m1/tema1/objects/Projectile.h"
#include "lab_m1/tema1/Constants.h"

using namespace Tema1Constants;

class Turret : public Object_2D {
public:
	Turret(const char* name, glm::vec2 position, glm::vec3 color, int cost);
	~Turret();

	void Fire();
	void Update(float deltaTime);
	void Draw(Shader* shader, const glm::mat4 viewMatrix, const glm::mat4 projectionMatrix) override;
	void Destroy();

	bool ShouldRemove();

	void RemoveProjectile();

	Projectile* GetProjectile();
	int GetCost();

private:
	void InitVertices() override;

	int cost;

	Projectile* projectile;

	float timeCounter;

	bool isDestroied;

	float scaleFactorDestroy;
};