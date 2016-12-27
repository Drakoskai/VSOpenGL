#version 450 core

uniform mat4 projection;
uniform mat4 modelView;
uniform vec3 viewPos;

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vNormal;

out VS_OUT
{
	vec4 worldpos;
	vec4 normal;
} vs_out;

void main()
{
	vec4 position = projection * modelView * vec4(vPosition, 1.0f);
	gl_Position = position;
	vs_out.worldpos = position;
	vs_out.normal = vec4(mat3(modelView) * vNormal,1.0f);
}
