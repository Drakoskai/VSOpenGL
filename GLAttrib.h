#pragma once

#include <gl/GL.h>

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

struct GLAttrib
{
	virtual ~GLAttrib() { }
	virtual int Index();
	virtual int Size();
	virtual int Type();
	virtual int OffSet();

};

struct Position : GLAttrib
{
	int Index() override
	{
		return GLAttribs::PositionIndex;
	}

	int Size() override
	{
		return GLAttribs::PositionSize;
	}

	int Type() override
	{
		return GLAttribs::PositionType;
	}

	int OffSet() override
	{
		return GLAttribs::PositionOffset;
	}

};

struct Normal : GLAttrib
{
	int Index() override
	{
		return  GLAttribs::NormalIndex;
	}

	int Size() override
	{
		return  GLAttribs::NormalSize;
	}

	int Type() override
	{
		return  GLAttribs::NormalType;
	}

	int OffSet() override
	{
		return  GLAttribs::NormalOffset;
	}

};

struct Color : GLAttrib
{
	int Index() override
	{
		return  GLAttribs::ColorIndex;
	}

	int Size() override
	{
		return  GLAttribs::ColorSize;
	}

	int Type() override
	{
		return  GLAttribs::ColorType;
	}

	int OffSet() override
	{
		return  GLAttribs::ColorOffset;
	}

};
