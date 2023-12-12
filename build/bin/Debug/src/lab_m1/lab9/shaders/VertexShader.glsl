#version 330

// Input
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;
layout(location = 3) in vec3 v_color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

uniform float time;
uniform bool isEarthTexture;

uniform bool isGrassTexture;
uniform float angle;

// Output
out vec2 texcoord;
out vec3 fragmentPosition;

void main()
{
    // TODO(student): Pass v_texture_coord as output to fragment shader
    texcoord = v_texture_coord;

    if (isEarthTexture) {
        texcoord = vec2(texcoord.x - time, texcoord.y);
    }

    if (isGrassTexture) {
        gl_Position = Projection * View * Model * vec4(v_position.x * cos(angle),  v_position.y, v_position.z * sin(angle), 1.0);
    } else {
        gl_Position = Projection * View * Model * vec4(v_position, 1.0);
    }

}
