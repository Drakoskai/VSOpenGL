#pragma once

#include "Model.h"

class Pyramid : Model
{
public:
	Pyramid();
	~Pyramid() override;
	bool Init(GLDrawContext dc) override;
	void GetTransform() override;
	void Update(float dt) override;
	void Release(GLDrawContext dc) override;

private:
	float hieght;
	float width;
	float depth;
};