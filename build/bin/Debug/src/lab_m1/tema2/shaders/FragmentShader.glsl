#version 330

// input
in vec3 color;

// Output
layout(location = 0) out vec4 outColor;

void main()
{
    // TODO(student): Write pixel out color
    outColor = vec4(color, 1);
}
