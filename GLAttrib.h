#pragma once

#include <GL/GL.h>

enum Attrib
{
	Position = 0,
	Color = 1,
	Normal = 2,
	Texture0 = 3,
	Texture1 = 4
};

namespace GLAttribs
{
	static const int PositionIndex = 0;
	static const int PositionSize = 3;
	static const int PositionType = GL_FLOAT;
	static const int PositionOffset = 0;

	static const int NormalIndex = 1;
	static const int NormalSize = 3;
	static const int NormalType = GL_FLOAT;
	static const int NormalOffset = PositionSize * sizeof(float);

	static const int ColorIndex = 2;
	static const int ColorSize = 4;
	static const int ColorType = GL_FLOAT;
	static const int ColorOffset = NormalOffset * sizeof(float);
}

