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
		colliders.remove(collider);
	}

	list<Collider*> GetColliders() {
		return colliders;
	}

	bool IsInCollision(Collider* collider) {
		for each (auto c in colliders) {
			if (c == collider) {
				continue;
			}

			if (c->IsInCollision(collider)) {
				return true;
			}
		}

		return false;
	}

private:

	list<Collider*> colliders;
};