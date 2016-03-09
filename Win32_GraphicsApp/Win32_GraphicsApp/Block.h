#pragma once

#include <GfxLib\Sprite.h>

class CBlock : public GFXLIB::CSprite
{
public:
	CBlock();
	~CBlock();

	// Geerbt über CSprite
	virtual void Init(GFXLIB::crVec2 pos) override;
	virtual void Update(float dt) override;
};

