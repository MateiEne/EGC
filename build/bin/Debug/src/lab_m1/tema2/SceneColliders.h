#pragma once

#include "Collider.h"

#include <list>

using namespace std;

class SceneColliders {
public:
	static SceneColliders& GetInstance() {
		static SceneColliders instance;

		return instance;
	}

	SceneColliders(SceneColliders const&) = delete;
	void operator=(SceneColliders const&) = delete;


private:
	SceneColliders() {}

	SceneColliders(SceneColliders&); // dont implement

	//void operator=(SceneColliders const&); // dont implement

public:
	void AddCollider(Collider* collider) {
		colliders.push_back(collider);
	}

	void DeleteCollider(Collider* collider) {
		for (int i = 0; i < colliders.size(); i++) {
			if (colliders[i] == collider) {
				colliders.erase(colliders.begin() + i);

				return;
			}
		}
	}

	void CheckCollisions() {
		list<pair<Collider*, Collider*>> damagedColliders;

		for (int i = 0; i < colliders.size() - 1; i++) {
			for (int j = i + 1; j < colliders.size(); j++) {
				if (colliders[j]->IsInCollision(colliders[i])) {
					damagedColliders.push_back(make_pair(colliders[i], colliders[j]));
				}
			}
		}

		for each (auto pair in damagedColliders) {
			pair.first->TakeDamage(pair.second);
			pair.second->TakeDamage(pair.first);
		}
	}

private:

	vector<Collider*> colliders;
};