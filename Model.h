#pragma once

#include "GLDrawContext.h"

class Model
{
public:
	virtual ~Model();
	virtual bool Init(GLDrawContext dc);
	virtual void GetTransform();
	virtual void Update(float dt);
	virtual void Release(GLDrawContext dc);
};
