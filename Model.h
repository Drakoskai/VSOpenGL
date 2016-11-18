#pragma once

#include "GLDrawContext.h"

/**
 * Contract for behavior of a drawable object 
 */
class Model
{
public:
	virtual ~Model() { }
	virtual bool Init(GLDrawContext dc) = 0;
	virtual void GetTransform() = 0;
	virtual void Update(float dt) = 0;
	virtual void Release(GLDrawContext dc) = 0;
};
