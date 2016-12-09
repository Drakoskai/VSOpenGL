#version 450 core

uniform mat4 mvp;
uniform mat4 model;
 
layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vNormal;

layout (location = 0) out vec3 interpolatedColor;

void main()
{
	gl_Position = mvp * (model * vec4(vPosition, 1.0));

	interpolatedColor = vec3(clamp(vPosition, 0, 1));
}
