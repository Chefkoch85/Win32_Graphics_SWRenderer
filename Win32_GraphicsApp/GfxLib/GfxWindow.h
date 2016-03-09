#pragma once

#include "GfxLib.h"
#include <Windows.h>

namespace GFXLIB
{
	class CGfxWindow
	{
	public:
		CGfxWindow();
		virtual ~CGfxWindow();

	public:
		virtual eResult Init(GFXLIB::crCStr title, GFXLIB::crVec4 bounds, HINSTANCE hInstance, WNDPROC wndProc);
		virtual eResult Destroy();

		virtual void SwapBuffers();

		void ClearBuffer();
		pScreenBuffer GetBackBuffer() { return mpBackBuffer; }
		Vec2 GetSize() { return { mWidth, mHeight }; }
		HWND GetHandle() { return mhWnd; }
		cCStr GetTitle() { return mTitle; }

	protected:
		cCStr mWinClassName = "GfxLib_Wnd_Type";
		BITMAPINFO mBitmapInfo = { 0 };
		HDC mhDC = nullptr;
		float mWidth, mHeight;
		pScreenBuffer mpBackBuffer = nullptr;
		HWND mhWnd = nullptr;
		HINSTANCE mhInstance = nullptr;
		CStr mTitle;
	};

}