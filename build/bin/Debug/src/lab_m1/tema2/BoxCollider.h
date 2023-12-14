#pragma once

class BoxCollider {
public:
	virtual float GetLength() = 0; // x
	virtual float GetHeight() = 0; // y
	virtual float GetWidth() = 0; // z

	virtual glm::vec3 GetCenter() = 0;

	bool IsInCollision(BoxCollider* other) {
		float length = GetLength();
		float otherLength = other->GetLength();
		
		float width = GetWidth();
		float otherWidth = other->GetWidth();

		float height = GetHeight();
		float otherHeight = other->GetHeight();

		glm::vec3 center = GetCenter();
		glm::vec3 otherCenter = other->GetCenter();

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
};