#version 450 core
#pragma debug(on)

in TCS_IN{
	vec4 worldpos;
	vec4 normal;
} tcs_in[];

out TCS_OUT
{
	vec4 worldpos;
	vec4 normal;
} tsc_out[];

layout (vertices = 3) out;

void main()
{
    if (gl_InvocationID == 0)                                                      
    {                                                                            
		gl_TessLevelInner[0] = 5.0;
		gl_TessLevelOuter[0] = 5.0;                                             
		gl_TessLevelOuter[1] = 5.0;                                         
		gl_TessLevelOuter[2] = 5.0;     

		for(int i = 0; i< tcs_in.length(); i++)
		{
			tsc_out[i].worldpos = tcs_in[i].worldpos;
			tsc_out[i].normal = tcs_in[i].normal;
		}
	}

	gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
}