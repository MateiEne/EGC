#include "lab_m1/tema1/objects/Object_2D.h"

Object_2D::Object_2D(const char* name, glm::vec2 position, glm::vec3 color) {
	this->name = name;
	this->color = color;

	objectMesh = new Mesh(name);

	Translate(position);

	radius = 0;
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

void Object_2D::CreateMesh()
{
	unsigned int VAO = 0;
	// TODO(student): Create the VAO and bind it
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO = 0;
	// TODO(student): Create the VBO and bind it
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// TODO(student): Send vertices data into the VBO buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	unsigned int IBO = 0;
	// TODO(student): Create the IBO and bind it
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	// TODO(student): Send indices data into the IBO buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

	// ========================================================================
	// This section demonstrates how the GPU vertex shader program
	// receives data. It will be learned later, when GLSL shaders will be
	// introduced. For the moment, just think that each property value from
	// our vertex format needs to be sent to a certain channel, in order to
	// know how to receive it in the GLSL vertex shader.

	// Set vertex position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

	// Set vertex normal attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

	// Set texture coordinate attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

	// Set vertex color attribute
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
	// ========================================================================

	// TODO(student): Unbind the VAO
	glBindVertexArray(0);
	// Check for OpenGL errors
	if (GetOpenGLError() == GL_INVALID_OPERATION)
	{
		cout << "\t[NOTE] : For students : DON'T PANIC! This error should go away when completing the tasks." << std::endl;
		cout << "\t[NOTE] : For developers : This happens because OpenGL core spec >=3.1 forbids null VAOs." << std::endl;
	}

	// Mesh information is saved into a Mesh object
	objectMesh->InitFromBuffer(VAO, static_cast<unsigned int>(indices.size()));

	//meshes[name] = new Mesh(name);
	//meshes[name]->InitFromBuffer(VAO, static_cast<unsigned int>(indices.size()));
}