#version 450 core

uniform mat4 modelViewProject;

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vNormal;

layout (location = 0) out vec3 interpolatedColor;

void main()
{
	interpolatedColor = vec3(clamp(vPosition, 0, 1));
	gl_Position = modelViewProject * vec4(vPosition, 1.0);	
}
