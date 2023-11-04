#include "lab_m1/tema1/objects/Enemy.h"

#include "core/engine.h"
#include "utils/glm_utils.h"

#include <vector>
#include <iostream>

using namespace std;

Enemy::Enemy(const char* name, glm::vec3 position)
{
	this->name = name;
	this->position = position;
}

Enemy::~Enemy()
{
}

void Enemy::Init()
{
	vertices.insert(vertices.end(), {
		// position, color, norm
		VertexFormat(glm::vec3(-1, 0.4f, -1), glm::vec3(0, 1, 1), glm::vec3(0, 1, 0)), // A - 0
		VertexFormat(glm::vec3(0, 1, -1), glm::vec3(0, 1, 1), glm::vec3(0, 1, 0)), // B - 1
		VertexFormat(glm::vec3(0.98f, 0.38f, -1), glm::vec3(0, 1, 1), glm::vec3(0, 1, 0)), // C - 2
		VertexFormat(glm::vec3(1.02f, -0.42f, -1), glm::vec3(0, 1, 1), glm::vec3(0, 1, 0)), // D - 3
		VertexFormat(glm::vec3(0, -1, -1), glm::vec3(0, 1, 1), glm::vec3(0, 1, 0)), // E - 4
		VertexFormat(glm::vec3(-1, -0.4f, -1), glm::vec3(0, 1, 1), glm::vec3(0, 1, 0)), // F - 5
		VertexFormat(glm::vec3(0, 0.4f, 0), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0)), // G - 6
		VertexFormat(glm::vec3(0.4f, 0.2f, 0), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0)), // H - 7
		VertexFormat(glm::vec3(0.4f, -0.2f, 0), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0)), // I - 8
		VertexFormat(glm::vec3(0, -0.4f, 0), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0)), // J - 9
		VertexFormat(glm::vec3(-0.4f, -0.2f, 0), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0)), // K - 10
		VertexFormat(glm::vec3(-0.4f, 0.2f, 0), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0)), // L - 11
		});

	indices.insert(indices.end(), {
		0, 1, 2, // ABC
		0, 2, 3, // ACD
		0, 3, 4, // ADE
		0, 4, 5, // AEF
		11, 6, 7, // LGH
		11, 7, 8, // LHI
		11, 8, 9, // LIJ
		11, 9, 10, // LJK
		});

	turretMesh = new Mesh(name);
	CreateMesh();
}

glm::vec3 Enemy::GetPosition()
{
	return position;
}

Mesh* Enemy::GetMesh()
{
	return turretMesh;
}

void Enemy::CreateMesh()
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
	turretMesh->InitFromBuffer(VAO, static_cast<unsigned int>(indices.size()));

	//meshes[name] = new Mesh(name);
	//meshes[name]->InitFromBuffer(VAO, static_cast<unsigned int>(indices.size()));
}