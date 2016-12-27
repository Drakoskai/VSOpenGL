#version 450 core

layout (triangles) in;
layout (triangle_strip) out;
layout (max_vertices = 3) out;

in VS_OUT
{
	vec4 worldpos;
	vec4 normal;
} gs_in[];

out GS_OUT
{
	vec4 worldpos;
	vec4 normal;
} gs_out;

uniform float explosionCoeffecient = 0.3;  

void main(void)
{
	vec3 ab = gl_in[1].gl_Position.xyz - gl_in[0].gl_Position.xyz;   
	vec3 ac = gl_in[2].gl_Position.xyz - gl_in[0].gl_Position.xyz; 
	
	vec3 faceNorm = -normalize(cross(ab, ac));   
	
	for(int i = 0; i < gl_in.length(); i++)
	{
		//vec3 faceNorm = -normalize(gs_in[i].normal.xyz);
		gl_Position = gl_in[i].gl_Position + vec4(faceNorm * explosionCoeffecient, 0.0);
		gs_out.worldpos = gs_in[i].worldpos + vec4(faceNorm * explosionCoeffecient, 0.0);
		gs_out.normal = gs_in[i].normal + vec4(faceNorm * explosionCoeffecient, 0.0);
		EmitVertex();
	}
	
	EndPrimitive();
}
