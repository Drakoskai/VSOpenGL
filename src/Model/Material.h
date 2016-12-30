#pragma once

#include "../Math3d/Vector.h"

struct MaterialProperties
{
	Math3d::Color Ambient;
	Math3d::Color Specular;
	Math3d::Color Emissive;
	float SpecularPower;
};

class Material
{	
public:

	Material();
	~Material();
	void Enable(bool enable);
};


