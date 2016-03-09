#include "Sprite.h"

using namespace GFXLIB;

CSprite::CSprite()
{
}


CSprite::~CSprite()
{
}

void CSprite::Init(GFXLIB::crVec2 pos)
{
	mPosition = pos;
	mSize = Vec2(64.0f, 64.0f);
	mData.Width = (int)mSize.Width;
	mData.Height = (int)mSize.Height;
	mData.Buffer = new Byte[(int)(mSize.Width * mSize.Height * BYTES_PER_PIXEL)];
	memset(mData.Buffer, 0xFF, (int)(mSize.Width * mSize.Height * BYTES_PER_PIXEL));
	int colWidth = 30;
	int offset = ((int)mSize.Width - colWidth) / 2;
	for (int y = 4; y < (int)mSize.Height - 4; y++)
	{
		for (int x = 0; x < colWidth; x++)
		{
			if (x < (int)(colWidth / 3 + 0.5f))
			{
				GFXLIB::SetPixel(offset + x, y, { 0x00,0xFF,0x00,0xFF }, mData);
			}
			else if (x < (int)((colWidth / 3) * 2 + 0.5f))
			{
				GFXLIB::SetPixel(offset + x, y, { 0x00,0x00,0xFF,0xFF }, mData);
			}
			else if (x < colWidth)
			{
				GFXLIB::SetPixel(offset + x, y, { 0xFF,0x00,0x00,0xFF }, mData);
			}
		}
	}

}

void CSprite::Render(GFXLIB::SGfxBuffer& backBuffer)
{
	GFXLIB::SetBlock((int)mPosition.X, (int)mPosition.Y, (int)mSize.Width, (int)mSize.Height, mData, backBuffer);
}
