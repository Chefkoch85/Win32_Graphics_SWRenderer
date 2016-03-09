#pragma once

#include <string>
#include <iostream>

namespace GFXLIB
{
	typedef unsigned char Byte;

	// 1. byte = B; 2. byte = G; 3. byte = R
	typedef Byte* pScreenBuffer;

	typedef std::string CStr;
	typedef const std::string cCStr;
	typedef const std::string& crCStr;

	static const int BYTES_PER_PIXEL = 4;
	
#define Cout std::cout
#define Cnl std::endl

	struct Vec2
	{
		union
		{
			float X;
			float T;
			float Width;
		};
		union
		{
			float Y;
			float U;
			float Height;
		};

		Vec2() : X(0.0f), Y(0.0f)
		{}
		Vec2(float x, float y) : X(x), Y(y)
		{}
	};

	struct Vec3
	{
		union 
		{
			float X;
			Byte R;
		};
		union
		{
			float Y;
			Byte G;
		};
		union
		{
			float Z;
			Byte B;
		};

		Vec3() : X(0.0f), Y(0.0f), Z(0.0f)
		{}
		Vec3(float x, float y, float z) : X(x), Y(y), Z(z)
		{}
		Vec3(int r, int g, int b) : R((Byte)r), G(g), B(b)
		{}
	};

	struct Vec4
	{
		union 
		{
			float X;
			Byte R;
		};
		union 
		{
			float Y;
			Byte G;
		};
		union
		{
			float Z;
			float Width;
			Byte B;
		};
		union
		{
			float W;
			float Height;
			Byte A;
		};

		Vec4() : X(0.0f), Y(0.0f), Z(0.0f), W(1.0f)
		{}
		Vec4(float x, float y, float z, float w) : X(x), Y(y), Z(z), W(w)
		{}
		Vec4(int r, int g, int b, int a = 255) : R((Byte)r), G(g), B(b), A(a)
		{}
	};

	typedef const Vec2 cVec2;
	typedef const Vec3 cVec3;
	typedef const Vec4 cVec4;

	typedef const Vec2& crVec2;
	typedef const Vec3& crVec3;
	typedef const Vec4& crVec4;

	struct SGfxBuffer
	{
		// 1. byte = B; 2. byte = G; 3. byte = R
		pScreenBuffer Buffer;
		int Width, Height;
	};

	void SetPixel(int x, int y, crVec4 col, SGfxBuffer& buffer);
	cVec4 GetPixel(int x, int y, SGfxBuffer& buffer);
	void SetRow(int xDest, int yDest, int ySrc, SGfxBuffer& data, SGfxBuffer& buffer);
	void SetBlock(int x, int y, int w, int h, crVec4 col, SGfxBuffer& buffer);
	void SetBlock(crVec4 bounds, crVec4 col, SGfxBuffer& buffer);
	void SetBlock(int x, int y, int w, int h, SGfxBuffer& data, SGfxBuffer& buffer);
	void SetBlock(crVec4 bounds, crVec4 col, SGfxBuffer& data, SGfxBuffer& buffer);

	enum class eResult
	{
		// Result all was OK
		OK,
		// Result an Error occurs
		FAIL,
		// Error on INIT
		F_INIT,
		// Error on RUN
		F_RUN,
		// Error on EXIT
		F_EXIT,
	};

}