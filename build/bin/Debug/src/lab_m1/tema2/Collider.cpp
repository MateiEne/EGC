#include "Collider.h"
#include "CollisionAlgorithms.h"

#include "SphereCollider.h"
#include "BoxCollider.h"


bool Collider::IsInCollision(Collider* other) {
	ColliderType type = GetColliderType();
	ColliderType otherType = other->GetColliderType();

	switch (type)
	{
	case SPHERE:
		switch (otherType)
		{
		case SPHERE:
		{
			SphereCollider* sphereA = static_cast<SphereCollider*>(this);
			SphereCollider* sphereB = static_cast<SphereCollider*>(other);

			return CA::IsCollisionSphereToSphere(sphereA, sphereB);
		}

		case BOX:
		{
			BoxCollider* box = static_cast<BoxCollider*>(other);
			SphereCollider* sphere = static_cast<SphereCollider*>(this);

			return CA::IsCollisionBoxToSphere(box, sphere);

		}
		}

		break;

	case BOX:
		switch (otherType)
		{
		case SPHERE:
		{
			BoxCollider* box = static_cast<BoxCollider*>(this);
			SphereCollider* sphere = static_cast<SphereCollider*>(other);

			return CA::IsCollisionBoxToSphere(box, sphere);
		}

		case BOX:
		{
			BoxCollider* boxA = static_cast<BoxCollider*>(this);
			BoxCollider* boxB = static_cast<BoxCollider*>(other);

			return CA::IsCollisionBoxToBox(boxA, boxB);

		}
		}

		break;

	default:
		break;
	}

	return false;
}
