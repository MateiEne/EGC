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

float rand3D(vec3 co){
    return fract(sin(dot(co.xyz ,vec3(12.9898,78.233,144.7272))) * 43758.5453);
}

void main()
{
    int darknessLevel = maxHp - hp;

    color = objectColor - vec3((50 * darknessLevel) / 256.f);  

    vec3 newPosition = v_position + vec3(rand3D(v_position) * darknessLevel / 10);

    // TODO(student): Compute gl_Position
    gl_Position = Projection * View * Model * vec4(newPosition, 1.0);
}
