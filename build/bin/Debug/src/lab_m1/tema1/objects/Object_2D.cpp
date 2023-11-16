#include "lab_m1/tema1/objects/Object_2D.h"

Object_2D::Object_2D(const char* name, glm::vec2 position, glm::vec3 color) {
	this->name = name;
	this->color = color;

	objectMesh = new Mesh(name);

	Translate(position);
	//SetPosition(position);

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

void Object_2D::Draw(Shader* shader, const glm::mat4 viewMatrix, const glm::mat4 projectionMatrix) {
	if (!objectMesh || !shader || !shader->program)
		return;

	shader->Use();
	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	glm::mat3 mm = GetModelMatrix();
	glm::mat4 model = glm::mat4(
		mm[0][0], mm[0][1], mm[0][2], 0.f,
		mm[1][0], mm[1][1], mm[1][2], 0.f,
		0.f, 0.f, mm[2][2], 0.f,
		mm[2][0], mm[2][1], 0.f, 1.f);

	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(model));
	objectMesh->Render();
}

void Object_2D::DrawDebug(Shader* shader, const glm::mat4 viewMatrix, const glm::mat4 projectionMatrix) {
	if (!GetDebugMesh() || !shader || !shader->program)
		return;

	shader->Use();
	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	glm::mat3 mm = GetModelMatrix();
	glm::mat4 model = glm::mat4(
		mm[0][0], mm[0][1], mm[0][2], 0.f,
		mm[1][0], mm[1][1], mm[1][2], 0.f,
		0.f, 0.f, mm[2][2], 0.f,
		mm[2][0], mm[2][1], 0.f, 1.f);

	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(model));
	GetDebugMesh()->Render();
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

glm::vec2 Object_2D::GetPosition() {
	return position;
}

glm::vec3 Object_2D::GetColor() {
	return color;
}

bool Object_2D::IsCoordInObject(glm::vec2 coord) {
	float distance = sqrt((coord.x - position.x) * (coord.x - position.x) + (coord.y - position.y) * (coord.y - position.y));

	if (distance < GetRadius()) {
		return true;
	}

	return false;
}

bool Object_2D::IsInCollision(Object_2D* object) {
	if (object == nullptr) {
		return false;
	}

	float distance = sqrt((object->position.x - position.x) * (object->position.x - position.x)
		+ (object->position.y - position.y) * (object->position.y - position.y));

	if (distance <= (GetRadius() + object->GetRadius())) {
		return true;
	}

	return false;
}

bool Object_2D::IsTheSameColor(Object_2D* object) {
	if (object == nullptr) {
		return false;
	}

	return GetColor() == object->GetColor();
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