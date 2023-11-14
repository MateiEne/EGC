#version 330

// Input
// TODO(student): Get values from vertex shader
in vec3 fragmentPosition;
in vec3 fragmentNormal;
in vec3 fragmentTexture;
in vec3 fragmentColor;

// Output
layout(location = 0) out vec4 outColor;
layout(location = 1) out vec4 outNormal;
layout(location = 2) out vec4 outTexture;

void main()
{
    // TODO(student): Write pixel out color
    //outColor = vec4(fragmentColor, 1);
    outColor = vec4(fragmentNormal, 1);
    outNormal = vec4(fragmentNormal, 1);
    outTexture = vec4(fragmentTexture, 1);
}
