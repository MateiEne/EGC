#include "lab_m1/tema1/objects/Object_2D.h"

Object_2D::Object_2D(const char* name, glm::vec2 position, glm::vec3 color) {
	this->name = name;
	this->color = color;

	objectMesh = new Mesh(name);

	Translate(position);

	radius = 0;

	drawMode = GL_TRIANGLES;
}


Object_2D::~Object_2D()
{
}

void Object_2D::Init()
{
	InitVertices();

	CreateMesh();

	radius = CalculateRadius();
}

float Object_2D::GetRadius()
{
	return max(scale.x, scale.y) * radius;
}

float Object_2D::CalculateRadius() {
	float maxDistance = 0;

	for each (auto vertex in vertices) {
		// TODO: calculate mesh origin with alebric sum
		float distance = sqrt(vertex.position.x * vertex.position.x + vertex.position.y * vertex.position.y);

		if (maxDistance <= distance) {
			maxDistance = distance;
		}
	}

	return maxDistance;
}

Mesh* Object_2D::GetMesh()
{
	return objectMesh;
}

Mesh* Object_2D::GetDebugMesh() {
	std::vector<VertexFormat> vertices;
	std::vector<unsigned int> indices;

	const float deg2rad = 3.14159 / 180;
	for (int i = 0; i <= 360; i++)
	{
		float degInRad = i * deg2rad;
		vertices.push_back(VertexFormat(
			glm::vec3((float)cos(degInRad) * radius, (float)sin(degInRad) * radius, 0),
			glm::vec3(1, 0, 0)));

		indices.push_back(i);
	}

	Mesh* dm = new Mesh("Debug");
	dm->SetDrawMode(GL_LINE_LOOP);
	dm->InitFromData(vertices, indices);

	return dm;
}

void Object_2D::CreateMesh() {
	objectMesh->SetDrawMode(drawMode);
	objectMesh->InitFromData(vertices, indices);
}