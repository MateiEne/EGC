#version 330

// Input
layout(location = 0) in vec3 v_position;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

uniform vec3 objectColor;
out vec3 color;

uniform int hp;
uniform int maxHp;

void main()
{
    int darknessLevel = maxHp - hp;

    color = objectColor - vec3((90 * darknessLevel) / 256.f, (90 * darknessLevel) / 256.f, (90 * darknessLevel) / 256.f);  

    // TODO(student): Compute gl_Position
    gl_Position = Projection * View * Model * vec4(v_position, 1.0);
}
