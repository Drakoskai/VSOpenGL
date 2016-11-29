#pragma once

#include "Vector.h"

struct VertexP2C
{
	Vector2f pos;
	Color color;

} VertexP2C;

struct VertexP2CI
{
	Vector2f pos;
	Color color;
	short idx;

} VertexP2CI;


struct VertexP3C
{
	Vector3f pos;
	Color color;

} VertexP3C;
