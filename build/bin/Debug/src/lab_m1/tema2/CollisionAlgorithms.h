#pragma once

#include "BoxCollider.h"
#include "SphereCollider.h"



namespace CA {
	bool IsCollisionBoxToBox(BoxCollider* boxA, BoxCollider* boxB) {
		float length = boxA->GetLength();
		float otherLength = boxB->GetLength();

		float width = boxA->GetWidth();
		float otherWidth = boxB->GetWidth();

		float height = boxA->GetHeight();
		float otherHeight = boxB->GetHeight();

		glm::vec3 center = boxA->GetCenter();
		glm::vec3 otherCenter = boxB->GetCenter();

		float minX = center.x - length;
		float minY = center.y - height;
		float minZ = center.z - width;

		float otherMinX = otherCenter.x - otherLength;
		float otherMinY = otherCenter.y - otherHeight;
		float otherMinZ = otherCenter.z - otherWidth;

		float maxX = center.x + length;
		float maxY = center.y + height;
		float maxZ = center.z + width;

		float otherMaxX = otherCenter.x + otherLength;
		float otherMaxY = otherCenter.y + otherHeight;
		float otherMaxZ = otherCenter.z + otherWidth;

		// a.maxX >= b.minX &&
		//	a.minY <= b.maxY &&
		//	a.maxY >= b.minY &&
		//	a.minZ <= b.maxZ &&
		//	a.maxZ >= b.minZ

		return (
			minX <= otherMaxX &&
			maxX >= otherMinX &&
			minY <= otherMaxY &&
			maxY >= otherMinY &&
			minZ <= otherMaxZ &&
			maxZ >= otherMinZ
			);
	}

	bool IsCollisionBoxToSphere(BoxCollider* b, SphereCollider* s) {

		float boxMinX = b->GetCenter().x - b->GetLength() / 2;
		float boxMinY = b->GetCenter().y - b->GetHeight() / 2;
		float boxMinZ = b->GetCenter().z - b->GetWidth() / 2;

		float boxMaxX = b->GetCenter().x + b->GetLength() / 2;
		float boxMaxY = b->GetCenter().y + b->GetHeight() / 2;
		float boxMaxZ = b->GetCenter().z + b->GetWidth() / 2;

		float x = max(boxMinX, min(s->GetCenter().x, boxMaxX));
		float y = max(boxMinY, min(s->GetCenter().y, boxMaxY));
		float z = max(boxMinZ, min(s->GetCenter().z, boxMaxZ));

		float distance = sqrt(pow((x - s->GetCenter().x), 2) + pow((y - s->GetCenter().y), 2) + pow((z - s->GetCenter().z), 2));

		return distance < s->GetRadius();
	}

	bool IsCollisionSphereToSphere(SphereCollider* s1, SphereCollider* s2) {
		glm::vec3 center = s1->GetCenter();
		glm::vec3 otherCenter = s2->GetCenter();

		float distance = sqrt(pow((otherCenter.x - center.x), 2) + pow((otherCenter.y - center.y), 2) + pow((otherCenter.z - center.z), 2));

		return distance < (s1->GetRadius() + s2->GetRadius());
	}

}