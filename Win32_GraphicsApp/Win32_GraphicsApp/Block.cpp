#include "Block.h"

using namespace GFXLIB;

CBlock::CBlock()
{
}


CBlock::~CBlock()
{
}

void CBlock::Init(GFXLIB::crVec2 pos)
{
	mPosition = pos;
	mSize = Vec2(64.0f, 16.0f);
	mData.Width = (int)mSize.Width;
	mData.Height = (int)mSize.Height;
	mData.Buffer = new Byte[(int)(mSize.Width * mSize.Height * BYTES_PER_PIXEL)];
	memset(mData.Buffer, 0xFF, (int)(mSize.Width * mSize.Height * BYTES_PER_PIXEL));

	SetBlock({ 0.0f,0.0f,mSize.Width,mSize.Height }, { 80,24,8,255 }, mData);

	SetBlock({ 0.0f, mSize.Height - 6.0f, mSize.Width, 6.0f }, { 0,255,0,255 }, mData);
}

void CBlock::Update(float dt)
{
}
