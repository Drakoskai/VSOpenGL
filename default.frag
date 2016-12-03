#version 450 core

#define FRAG_COLOR  0

layout (location = 0) in vec3 interpolatedColor;

layout (location = FRAG_COLOR) out vec4 outputColor;

//uniform vec4 color_ambient = vec4(0.1, 0.2, 0.5, 1.0);
//uniform vec4 color_diffuse = vec4(0.2, 0.3, 0.6, 1.0);
//uniform vec4 color_specular = vec4(0.0);
//uniform float shininess = 77.0f;
//uniform vec3 light_position = vec3(12.0f, 32.0f, 560.0f);

void main()
{
    outputColor = vec4(interpolatedColor, 1.0);
}
