#pragma once

#include "GLDrawContext.h"
#include "Transform.h"

/**
 * Contract for behavior of a drawable object 
 */
class Model
{
public:
	virtual ~Model() { }
	virtual void Init(GLDrawContext * dc) = 0;
	virtual Transform GetTransform() = 0;
	virtual void Update(float dt) = 0;
	virtual void Release() = 0;
};
