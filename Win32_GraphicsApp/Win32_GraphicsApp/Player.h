#pragma once

#include <GfxLib\Sprite.h>

#include <vector>

#include "Block.h"

class CPlayer : public GFXLIB::CSprite
{
public:
	CPlayer();
	~CPlayer();

	// Geerbt über CSprite
	virtual void Init(GFXLIB::crVec2 pos, std::vector<CBlock>& level);
	virtual void Update(float dt) override;

	void Jump();
	void MoveLeft();
	void MoveRight();

private:
	bool CollideWithLevel();

	GFXLIB::Vec2 mVel;
	std::vector<CBlock*> mLevel;
};

