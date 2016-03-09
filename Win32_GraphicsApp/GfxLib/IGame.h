#pragma once

#include "GfxWindow.h"

namespace GFXLIB
{
	enum class eGameState
	{
		NONE,
		LOAD,
		UNLOAD,
		RUN,
		EXIT,
	};

	class IGame
	{
	public:
		virtual ~IGame();

		eResult GameInit(HINSTANCE hInstance, LPSTR lpCmdLine);
		eResult GameLoop();
		eResult GameExit();

	protected:
		IGame();
		virtual eResult onInit(HINSTANCE hInstance, LPSTR lpCmdLine) = 0;
		virtual eResult onExit() = 0;
		
		virtual void Update(float dt) = 0;
		virtual void Render() = 0;
		
	protected:
		CGfxWindow* mpWindow = nullptr;
		eGameState mGameState = eGameState::NONE;
		int mFPS = 60;

		SGfxBuffer mBackBuffer;
		float SecondsPerTick = 0.0f;
		LARGE_INTEGER mStartTicks, mEndTicks;
	};

}
