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
		//if (Missile* m = dynamic_cast<Missile*>(collider)) {
		//	cout << "mmmm" << endl;
		//}

		colliders.remove(collider);
	}

	list<Collider*> GetColliders() {
		return colliders;
	}

	void CheckCollisions() {
		for each (auto collider in colliders) {
			for each (auto c in colliders)
			{
				if (c == collider) {
					continue;
				}

				if (c->IsInCollision(collider)) {
					c->TakeDamage(collider);
					collider->TakeDamage(c);
				}

			}
		}
	}

	bool IsInCollision(Collider* collider) {
		for each (auto c in colliders) {
			if (c == collider) {
				continue;
			}

			if (c->IsInCollision(collider)) {
				c->TakeDamage(collider);
				collider->TakeDamage(c);

				return true;
			}
		}

		return false;
	}

private:

	list<Collider*> colliders;
};