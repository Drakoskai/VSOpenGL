#version 450 core

uniform mat4 modelViewProject;

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec4 vNormal;

void main()
{
	gl_Position = modelViewProject * vPosition;
}
