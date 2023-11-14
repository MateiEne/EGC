#version 330

// Input
// TODO(student): Get vertex attributes from each location
layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec3 vertexTexture;
layout(location = 3) in vec3 vertexColor;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform float time;

// Output
// TODO(student): Output values to fragment shader
out vec3 fragmentPosition;
out vec3 fragmentNormal;
out vec3 fragmentTexture;
out vec3 fragmentColor;

void main()
{
    // TODO(student): Send output to fragment shader
    fragmentPosition = vertexPosition;
    fragmentNormal = vertexNormal + sin(time);
    fragmentTexture = vertexTexture;
    fragmentColor = vertexColor + sin(time);

    // TODO(student): Compute gl_Position
    gl_Position = Projection * View * Model * vec4(vertexPosition + sin(time), 1.0);
}
