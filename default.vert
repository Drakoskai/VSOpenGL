#version 450 core

uniform mat4 modelViewProject;

layout(location = 0) in vec4 vPosition;

void main()
{
	gl_Position = modelViewProject * vPosition;
}
