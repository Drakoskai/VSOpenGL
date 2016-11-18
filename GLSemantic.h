#pragma once

struct Attr
{
	static const int Position = 0;
	static const int Normal = 1;
	static const int Color = 3;
	static const int TexCoord = 4;
	static const int DrawId = 5;

};

struct Buffer
{
	static const int Static = 0;
	static const int Dynamic = 1;

};

struct Frag
{
	static const int Color = 0;
	static const int Red = 0;
	static const int Green = 1;
	static const int Blue = 2;
	static const int Alpha = 0;

};

struct Object
{
	static const int Vao = 0;
	static const int Vbo = 1;
	static const int Ibo = 2;
	static const int Texture = 3;
	static const int Sampler = 4;
	static const int Size = 5;

};

struct Uniform
{
	static const int Material = 0;
	static const int Transform0 = 1;
	static const int Transform1 = 2;

};

struct Stream
{
	static const int _0 = 0;
	static const int _1 = 1;

};

