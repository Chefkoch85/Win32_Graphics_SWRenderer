#pragma once

#include "GfxLib.h"

namespace GFXLIB
{
	class CSprite
	{
	public:
		CSprite();
		virtual ~CSprite();

		virtual void Init(GFXLIB::crVec2 pos);

		virtual void Update(float dt) = 0;
		virtual void Render(GFXLIB::SGfxBuffer& backBuffer);

		void SetPos(crVec2 pos) { mPosition = pos; }
		crVec2 GetPos() { return mPosition; }
		crVec2 GetSize() { return mSize; }

	protected:
		// 1. byte = B; 2. byte = G; 3. byte = R
		GFXLIB::SGfxBuffer mData;
		GFXLIB::Vec2 mPosition;
		GFXLIB::Vec2 mSize;
	};

}
