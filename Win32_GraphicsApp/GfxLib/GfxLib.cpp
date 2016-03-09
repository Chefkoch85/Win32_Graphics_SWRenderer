#include "GfxLib.h"

using namespace GFXLIB;

void GFXLIB::SetPixel(int x, int y, crVec4 col, SGfxBuffer& buffer)
{
	if (x < 0)
		return;
	else if (y < 0)
		return;

	if (x >= buffer.Width)
		return;
	else if (y >= buffer.Height)
		return;

	Byte* destAddr = (Byte*)buffer.Buffer;
	if (col.A > 0)
	{
		destAddr[(x + y * buffer.Width) * BYTES_PER_PIXEL + 0] = col.B;
		destAddr[(x + y * buffer.Width) * BYTES_PER_PIXEL + 1] = col.G;
		destAddr[(x + y * buffer.Width) * BYTES_PER_PIXEL + 2] = col.R;
		destAddr[(x + y * buffer.Width) * BYTES_PER_PIXEL + 3] = col.A;
	}
}

cVec4 GFXLIB::GetPixel(int x, int y, SGfxBuffer& buffer)
{
	Byte* destAddr = (Byte*)buffer.Buffer;
	Byte B = destAddr[(x + y * buffer.Width) * BYTES_PER_PIXEL + 0];
	Byte G = destAddr[(x + y * buffer.Width) * BYTES_PER_PIXEL + 1];
	Byte R = destAddr[(x + y * buffer.Width) * BYTES_PER_PIXEL + 2];
	Byte A = destAddr[(x + y * buffer.Width) * BYTES_PER_PIXEL + 3];

	return Vec4(R, G, B, A);
}

void GFXLIB::SetRow(int xDest, int yDest, int ySrc, SGfxBuffer& data, SGfxBuffer& buffer)
{
	int w = data.Width;
	int h = data.Height;
	int oldX = 0;
	if (xDest < 0)
	{
		oldX = xDest;
		xDest = 0;
		w += oldX;
	}
	else if (yDest < 0)
		yDest = 0;

	if (xDest + data.Width >= buffer.Width)
		w = buffer.Width - xDest;

	int* destAddr = (int*)buffer.Buffer;
	destAddr += (int)(xDest + (yDest) * buffer.Width);
	int* srcAddr = (int*)data.Buffer;
	srcAddr += -oldX + ySrc * data.Width;
	memcpy(destAddr, srcAddr, w * BYTES_PER_PIXEL);
}

void GFXLIB::SetBlock(int x, int y, int w, int h, crVec4 col, SGfxBuffer& buffer)
{
	if (x < 0)
	{
		w += x;
		x = 0;
	}
	if (y < 0)
	{
		h += y;
		y = 0;
	}

	if (x + w >= buffer.Width)
		w = buffer.Width - x;
	if (y + h >= buffer.Height)
		h = buffer.Height - y;

	SGfxBuffer data;
	data.Buffer = (Byte*)malloc(w * BYTES_PER_PIXEL);
	data.Width = w;
	data.Height = 1;
	int* row = (int*)data.Buffer;
	for (int i = 0; i < w; i++)
	{
		row[i] = (((col.A << 24) | (col.R << 16) | col.G << 8) | col.B);
	}

	for (int dy = 0; dy < h; dy++)
	{
		SetRow(x, y + dy, 0, data, buffer);
	}

	free(data.Buffer);
}

void GFXLIB::SetBlock(crVec4 bounds, crVec4 col, SGfxBuffer & buffer)
{
	SetBlock((int)bounds.X, (int)bounds.Y, (int)bounds.Width, (int)bounds.Height, col, buffer);
}

void GFXLIB::SetBlock(int x, int y, int w, int h, SGfxBuffer & data, SGfxBuffer & buffer)
{
	if (x + data.Width < 0 ||
		y + data.Height < 0)
		return;

	if (x > buffer.Width ||
		y > buffer.Height)
		return;

	//if (x < 0)
	//{
	//	x = 0;
	//}
	if (y < 0)
	{
		y = 0;
	}

	if (x + w >= buffer.Width)
		w = buffer.Width - x;
	if (y + h >= buffer.Height)
		h = buffer.Height - y;

	for (int dy = 0; dy < h; dy++)
	{
		SetRow(x, y + dy, dy, data, buffer);
	}
}

void GFXLIB::SetBlock(crVec4 bounds, crVec4 col, SGfxBuffer & data, SGfxBuffer & buffer)
{
	SetBlock((int)bounds.X, (int)bounds.Y, (int)bounds.Width, (int)bounds.Height, data, buffer);
}
