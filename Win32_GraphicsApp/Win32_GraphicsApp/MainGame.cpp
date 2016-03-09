#include "MainGame.h"

using namespace GFXLIB;

CMainGame* CMainGame::mInstance = nullptr;

CMainGame::CMainGame()
{
}


CMainGame::~CMainGame()
{
}

LRESULT CMainGame::WindowCallback(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return Instance()->WindowProc(hWnd, msg, wParam, lParam);
}

LRESULT CMainGame::WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		mGameState = eGameState::EXIT;
		break;

	case WM_KEYUP:

		OutputDebugString((std::to_string(msg) + ":" + std::to_string(wParam) + "\n").c_str());

		if (wParam == VK_ESCAPE)
			mGameState = eGameState::EXIT;
		//else if (wParam == VK_SPACE)
		//{
		//	mRunLine = !mRunLine;

		//	if (!mRunLine)
		//		mRow = 0;
		//}
		else if (wParam == VK_ADD)
		{
			mNumSprites += 10;
		}
		else if (wParam == VK_SUBTRACT)
		{
			mNumSprites -= 10;
		}
		else if (wParam == VK_SPACE)
		{
			mPlayer.Jump();
		}
		else if (wParam == VK_LEFT)
		{
			mPlayer.MoveLeft();
		}
		else if (wParam == VK_RIGHT)
		{
			mPlayer.MoveRight();
		}

		return 0;

	case WM_SYSKEYUP:

		return 0;

	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}


CMainGame * CMainGame::Instance()
{
	if (mInstance)
		return mInstance;

	mInstance = new CMainGame();
	return mInstance;
}

eResult CMainGame::onInit(HINSTANCE hInstance, LPSTR lpCmdLine)
{
	eResult result = eResult::OK;

	mpWindow = new CGfxWindow();
	if ((result = mpWindow->Init("First Win32 Window", { 50.0f,50.0f,640.0f,480.0f }, hInstance, WindowCallback)) != eResult::OK)
	{
		return result;
	}

	mBackBuffer.Buffer = mpWindow->GetBackBuffer();
	mBackBuffer.Width = (int)mpWindow->GetSize().Width;
	mBackBuffer.Height = (int)mpWindow->GetSize().Height;

	mGround.resize(10);
	for (int i = 0; i < 10; i++)
	{
		int h = rand() % 180;
		mGround[i].Init({ 0.0f + i * 64.0f, 5.0f + h / 10.0f });
	}

	mPlayer.Init({ -10, 50 }, mGround);

	return result;
}

eResult CMainGame::onExit()
{
	if (mpWindow)
	{
		mpWindow->Destroy();
		delete mpWindow;
		mpWindow = nullptr;
	}
	return eResult::OK;
}

void CMainGame::Update(float dt)
{
	if (mRunLine)
	{
		mRow += 16.0f * dt;
	}

	if (mRow >= 240.0f)
		mRow -= 240.0f;

	mPlayer.Update(dt);

	CStr tmp = mpWindow->GetTitle() + " : " + std::to_string(mFPS) + " : " + std::to_string(mNumSprites);
	SetWindowText(mpWindow->GetHandle(), tmp.c_str());
}

void CMainGame::Render()
{
	//for (int i = 0; i < (int)mGround.size(); i++)
	//	mGround[i].Render(mBackBuffer);

	mPlayer.Render(mBackBuffer);

	//for (int i = 0; i < mNumSprites; i++)
	//	GFXLIB::SetBlock(600, 450, 100, 100, { 255,0,0,255 }, mBackBuffer);
}

