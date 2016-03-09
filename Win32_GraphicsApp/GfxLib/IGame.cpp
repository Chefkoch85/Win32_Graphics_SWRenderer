#include "IGame.h"

using namespace GFXLIB;

IGame::IGame()
{
}


IGame::~IGame()
{
}

eResult GFXLIB::IGame::GameInit(HINSTANCE hInstance, LPSTR lpCmdLine)
{
	eResult result = eResult::OK;

	result = onInit(hInstance, lpCmdLine);

	LARGE_INTEGER li = { 0 };
	// get tick frequency
	QueryPerformanceFrequency(&li);
	// calculate  seconds per tick
	SecondsPerTick = 1.0f / li.QuadPart;

	return result;
}

eResult GFXLIB::IGame::GameLoop()
{
	MSG msg = { 0 };
	float deltaTime = 0.016f;
	// calculate frame time for disered FPS
	const float preferredTime = 1.0f / 60.0f;
	float accu1 = 0.0f, accu2 = 0.0f, sumTime = 0.0f;
	int frameCounter = 0;

	// get first start ticks
	QueryPerformanceCounter(&mStartTicks);

	while (mGameState != eGameState::EXIT)
	{
		// get messages from Windows
		while (PeekMessage(&msg, mpWindow->GetHandle(), 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// add frame time in ms (for showing fps)
		sumTime += deltaTime * 1000.0f;
		// add frame time for update call
		accu1 += deltaTime;
		// add frame time for render call
		accu2 = accu1;

		// update if enough time has passed and 
		// iupdate more then one time if frame time is to tall
		while (accu1 >= preferredTime)
		{
			accu1 -= preferredTime;
			Update(preferredTime);
		}

		// render if enough time has passed
		if (accu2 >= preferredTime)
		{ 
			accu2 -= preferredTime;
			frameCounter++;

			mpWindow->ClearBuffer();
			Render();
			mpWindow->SwapBuffers();
		}

		if (sumTime >= 1000.0f)
		{
			mFPS = frameCounter;
			frameCounter = 0;
			sumTime = 0.0f;
		}

		// get end ticks
		QueryPerformanceCounter(&mEndTicks);
		// calculate frame ticks
		int Interval = (int)(mEndTicks.QuadPart - mStartTicks.QuadPart);
		// set current ticks to start ticks for next frame
		mStartTicks = mEndTicks;
		// calculate frame time
		deltaTime = Interval * SecondsPerTick;
	}

	return eResult::OK;
}

eResult GFXLIB::IGame::GameExit()
{
	eResult result = eResult::OK;

	result = onExit();

	return result;
}