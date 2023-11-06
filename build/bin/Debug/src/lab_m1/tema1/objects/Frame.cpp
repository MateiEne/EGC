#include "lab_m1/tema1/objects/Frame.h"

Frame::Frame(const char* name, glm::vec2 position, glm::vec3 color) : Object_2D(name, position, color) {
}

Frame::~Frame() {
}

void Frame::InitVertices()
{
	vertices.insert(vertices.end(), {
		// position, color, norm
		VertexFormat(glm::vec3(-0.5f, -0.5f, 0), color, glm::vec3(0, 1, 0)), // A - 0
		VertexFormat(glm::vec3(-0.5f, 0.5f, 0), color, glm::vec3(0, 1, 0)), // B - 1
		VertexFormat(glm::vec3(0.5f, 0.5f, 0), color, glm::vec3(0, 1, 0)), // C - 2
		VertexFormat(glm::vec3(0.5f, -0.5f, 0), color, glm::vec3(0, 1, 0)), // D - 3
		});

	indices.insert(indices.end(), {
		0, 1, 2, 3
		}
	);

	drawMode = GL_LINE_LOOP;
}