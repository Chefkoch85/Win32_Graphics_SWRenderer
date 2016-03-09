#include "Player.h"

using namespace GFXLIB;

CPlayer::CPlayer()
{
}


CPlayer::~CPlayer()
{
}

void CPlayer::Init(GFXLIB::crVec2 pos, std::vector<CBlock>& level)
{
	mLevel.resize(level.size());
	for (unsigned int i = 0; i < level.size(); i++)
		mLevel[i] = &level[i];

	mPosition = pos;
	mSize = Vec2(22.0f, 32.0f);
	mData.Width = (int)mSize.Width;
	mData.Height = (int)mSize.Height;
	mData.Buffer = new Byte[(int)(mSize.Width * mSize.Height * BYTES_PER_PIXEL)];
	memset(mData.Buffer, 0xFF, (int)(mSize.Width * mSize.Height * BYTES_PER_PIXEL));

	int col = 0xFFFF0000;

	int y = 31, w = (int)mSize.Width;
	int x = w / 2 - 2, xm = x;
	int* buf = (int*)mData.Buffer;
	//				   AARRGGBB
	buf[x + y * w] = col;
	x++;
	buf[x + y * w] = col;
	x++;
	buf[x + y * w] = col;
	x++;
	buf[x + y * w] = col;

	y--;
	x = xm - 1;
	buf[x + y * w] = col;
	x = xm + 4;
	buf[x + y * w] = col;

	y--;
	x = xm - 2;
	buf[x + y * w] = col;
	x = xm + 5;
	buf[x + y * w] = col;

	y--;
	x = xm - 2;
	buf[x + y * w] = col;
	x = xm + 5;
	buf[x + y * w] = col;

	y--;
	x = xm - 2;
	buf[x + y * w] = col;
	x = xm + 5;
	buf[x + y * w] = col;

	y--;
	x = xm - 2;
	buf[x + y * w] = col;
	x = xm + 5;
	buf[x + y * w] = col;

	y--;
	x = xm - 1;
	buf[x + y * w] = col;
	x = xm + 4;
	buf[x + y * w] = col;

	y--;
	x = xm;
	buf[x + y * w] = col;
	x++;
	buf[x + y * w] = col;
	x++;
	buf[x + y * w] = col;
	x++;
	buf[x + y * w] = col;

	// torso
	for (int i = 0; i < 10; i++)
	{
		y--;
		x = xm + 1;
		buf[x + y * w] = col;
		x++;
		buf[x + y * w] = col;
	}

	// left arm
	y = 20;
	x = xm + 1;
	for (int i = 0; i < 10; i++)
	{
		x--;
		if (i % 2)
			y++;

		buf[x + y * w] = col;
		buf[x + 1 + y * w] = col;
	}

	// right arm
	y = 20;
	x = xm + 1;
	for (int i = 0; i < 10; i++)
	{
		x++;
		if (i % 2)
			y++;

		buf[x + y * w] = col;
		buf[x + 1 + y * w] = col;
	}

	// left leg
	y = 14;
	x = xm + 1;
	for (int i = 0; i < 14; i++)
	{
		y--;
		if (i % 2)
			x--;
		buf[x + y * w] = col;
		buf[x + 1 + y * w] = col;
	}

	// right leg
	y = 14;
	x = xm + 1;
	for (int i = 0; i < 14; i++)
	{
		y--;
		if (i % 2)
			x++;
		buf[x + y * w] = col;
		buf[x + 1 + y * w] = col;
	}



}

void CPlayer::Update(float dt)
{
	const float GRAV = 9.81f * 4.0f;
	const float DEACC = 5.0f;
	bool isJumping = false;

	if (mVel.Y > 0.0f)
	{
		isJumping = true;
		mPosition.Y += mVel.Y * dt;
		mVel.Y -= GRAV * 2.0f * dt;
		if (mVel.Y <= 0.0f)
		{
			isJumping = false;
			mVel.Y = 0.0f;
		}
	}

	mPosition.X += mVel.X;
	if (mVel.X < 0.0f)
	{
		mVel.X += DEACC * dt;
		if (mVel.X >= 0.0f)
			mVel.X = 0.0f;
	}
	else if (mVel.X > 0.0f)
	{
		mVel.X -= DEACC * dt;
		if (mVel.X <= 0.0f)
			mVel.X = 0.0f;
	}

	// applay cravatiy
	float oldY = mPosition.Y;
	if (!isJumping)
		mPosition.Y -= GRAV * dt;
	

	if (CollideWithLevel())
		mPosition.Y = oldY;

	if (mPosition.Y < 0.0f)
		mPosition.Y = 0.0f;
}

bool CPlayer::CollideWithLevel()
{
	for (unsigned int i = 0; i < mLevel.size(); i++)
	{
		if (mPosition.X >= mLevel[i]->GetPos().X && 
			mPosition.X < mLevel[i]->GetPos().X + mLevel[i]->GetSize().Width)
		{
			if (mPosition.Y <= mLevel[i]->GetPos().Y + mLevel[i]->GetSize().Height)
				return true;
		}
	}

	return false;
}

void CPlayer::Jump()
{
	mVel.Y = 80.0f;
}

void CPlayer::MoveLeft()
{
	mVel.X += -2.0f;
}

void CPlayer::MoveRight()
{
	mVel.X += 2.0f;
}
