#version 450 core
#pragma debug(on)

uniform mat4 projection;
uniform mat4 modelView;
uniform vec3 viewPos;

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vNormal;

out vec3 vs_worldpos;
out vec3 vs_normal;

void main()
{
	vec4 position = projection * modelView * vec4(vPosition, 1.0);
	gl_Position = position;
	vs_worldpos = position.xyz;
	vs_normal = mat3(modelView) * vNormal;
}
