#version 450 core

#define FRAG_COLOR  0

uniform vec3 viewPos;

in VS_OUT
{
	vec4 worldpos;
	vec4 normal;
} fr_in;

layout (location = FRAG_COLOR) out vec4 outputColor;

uniform vec4 ambient = vec4(0.329412f, 0.223529f, 0.027451f, 1.0f);
uniform vec4 diffuse = vec4(0.780392f, 0.568627f, 0.113725f, 1.0f);
uniform vec4 specular = vec4(0.992157f, 0.941176f, 0.807843f, 1.0f );
uniform float shininess =  27.0f;
uniform vec3 lightPos = vec3(12.0f, 32.0f, 560.0f);

const float kPi = 3.14159265;

void main()
{
	vec3 lightDir = normalize(lightPos.xyz - fr_in.worldpos.xyz);
    vec3 normal = normalize(fr_in.normal.xyz);
		
	//Diffuse
    float diffuseCoefficient = max(dot(normal, lightDir), 0.0f);
	vec4 diff = diffuseCoefficient * diffuse;
	
	//Specular
	float specularCoefficient = 0.0;
	if(diffuseCoefficient > 0.0f)
	{
		const float kEnergyConservation = ( 8.0f + shininess ) / ( 8.0f * kPi ); 
		specularCoefficient =/* kEnergyConservation */ pow(max(dot(lightDir, reflect(-lightDir, normal)), 0.0f), shininess);
	}

	vec4 spec = specularCoefficient * specular;
	vec4 linearColor = ambient * (diff + spec);
	vec4 gamma = vec4(1.0/2.2);
    outputColor = vec4(pow(linearColor, gamma));
}
