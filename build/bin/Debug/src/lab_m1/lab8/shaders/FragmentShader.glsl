#version 330

// Input
in vec3 world_position;
in vec3 world_normal;

// Uniforms for light properties
uniform vec3 light_direction;
uniform vec3 light_position;
uniform vec3 eye_position;

uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;

// Uniforms for light properties
uniform vec3 second_light_direction;
uniform vec3 second_light_position;

// TODO(student): Declare any other uniforms
uniform vec3 object_color;
uniform int type_of_light;
uniform float cut_off_angle;

// Output
layout(location = 0) out vec4 out_color;



void main()
{
    vec3 N = normalize(world_normal);
    vec3 L = normalize(light_position - world_position);
	vec3 V = normalize(eye_position - world_position);
	vec3 H = normalize(L + V);

    // TODO(student): Define ambient, diffuse and specular light components
    float ambient_light = 0.25;
	float diffuse_light = material_kd * max(dot(normalize(N), L), 0);
    float specular_light = 0;
    // It's important to distinguish between "reflection model" and
    // "shading method". In this shader, we are experimenting with the Phong
    // (1975) and Blinn-Phong (1977) reflection models, and we are using the
    // Phong (1975) shading method. Don't mix them up!
    if (diffuse_light > 0) {
		specular_light = material_ks * pow(max(dot(normalize(N), H), 0), material_shininess);   
    }
    vec3 L_2 = normalize(second_light_position - world_position);
	vec3 H_2 = normalize(L_2 + V);

    // TODO(student): Define ambient, diffuse and specular light components
	float second_diffuse_light = material_kd * max(dot(normalize(N), L_2), 0);
    float second_specular_light = 0;
    // It's important to distinguish between "reflection model" and
    // "shading method". In this shader, we are experimenting with the Phong
    // (1975) and Blinn-Phong (1977) reflection models, and we are using the
    // Phong (1975) shading method. Don't mix them up!
    if (second_diffuse_light > 0) { 
		second_specular_light = material_ks * pow(max(dot(normalize(N), H_2), 0), material_shininess);   
    }


    // TODO(student): If (and only if) the light is a spotlight, we need to do
    // some additional things.

    // Compute light
	float light = 0;
	float second_light = 0;

	if (type_of_light == 1)
	{
		float cut_off_rad = radians(cut_off_angle);
		float spot_light = dot(-L, light_direction);
		float spot_light_limit = cos(cut_off_rad);
		
		if (spot_light > spot_light_limit) {	 
			// Quadratic attenuation
			float linear_att = (spot_light - spot_light_limit) / (1 - spot_light_limit);
			float light_att_factor = pow(linear_att, 2);
			light = ambient_light + light_att_factor * (diffuse_light + specular_light);
		} 
		else {
			light = ambient_light;  // There is no spot light, but there is light from other objects
		}

		second_light = 0;
	} 
	else {
		float d = distance(light_position, world_position);
		float attenuation_factor = 1 / (d * d + 1);

		
		float d_2 = distance(second_light_position, world_position);
		float attenuation_factor_2 = 1 / (d * d + 1);
		
		second_light = ambient_light + (second_diffuse_light + second_specular_light) * attenuation_factor_2;
		light = ambient_light + (diffuse_light + specular_light) * attenuation_factor;
	}
    // TODO(student): Compute the total light. You can just add the components
    // together, but if you're feeling extra fancy, you can add individual
    // colors to the light components. To do that, pick some vec3 colors that
    // you like, and multiply them with the respective light components.
	vec3 colour = object_color * (light + second_light);

    // TODO(student): Write pixel out color
    out_color = vec4(colour, 1);

}
