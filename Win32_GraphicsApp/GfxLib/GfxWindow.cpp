#include "GfxWindow.h"

using namespace GFXLIB;

CGfxWindow::CGfxWindow()
{

}


CGfxWindow::~CGfxWindow()
{
}

eResult GFXLIB::CGfxWindow::Init(GFXLIB::crCStr title, GFXLIB::crVec4 bounds, HINSTANCE hInstance, WNDPROC wndProc)
{
	mWidth = bounds.Width;
	mHeight = bounds.Height;
	mhInstance = hInstance;
	mTitle = title;

	WNDCLASSEX wndClass = { 0 };
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.lpfnWndProc = wndProc;
	wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wndClass.lpszClassName = mWinClassName.c_str();
	wndClass.hInstance = mhInstance;
	//wndClass.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wndClass))
		return eResult::F_INIT;

	DWORD dwStyleEx = 0;
	DWORD dwStyle = WS_OVERLAPPEDWINDOW;

	// handle fullscreen values
	// TODO

	// adjust window size to match client area to desired size
	RECT wRect;
	wRect.top = 0;
	wRect.left = 0;
	wRect.right = (LONG)mWidth;
	wRect.bottom = (LONG)mHeight;
	AdjustWindowRectEx(&wRect, dwStyle, FALSE, dwStyleEx);

	mhWnd = CreateWindowEx(
		dwStyleEx,					// extra style flags
		mWinClassName.c_str(),		// window class name
		mTitle.c_str(),				// window title
		dwStyle,					// normal style flags
		(int)bounds.X,				// window start position x
		(int)bounds.Y,				// window start position y
		wRect.right - wRect.left,	// adjusted window width
		wRect.bottom - wRect.top,	// adjusted window height
		nullptr,					// parent window, have none
		nullptr,					// menu bar, have none
		mhInstance,					// handle instance
		nullptr						// extra window data
		);

	if (!mhWnd)
		return eResult::F_INIT;

	ShowWindow(mhWnd, SW_NORMAL);

	// create backbuffer bitmap
	mBitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFO);
	mBitmapInfo.bmiHeader.biWidth = (LONG)mWidth;
	mBitmapInfo.bmiHeader.biHeight = (LONG)mHeight;
	mBitmapInfo.bmiHeader.biPlanes = 1;
	mBitmapInfo.bmiHeader.biBitCount = BYTES_PER_PIXEL * 8;
	mBitmapInfo.bmiHeader.biCompression = BI_RGB;

	mpBackBuffer = (Byte*)malloc((size_t)(mWidth * mHeight * BYTES_PER_PIXEL));
	memset(mpBackBuffer, 0, (size_t)(mWidth * mHeight * BYTES_PER_PIXEL));
	
	return eResult::OK;
}

eResult GFXLIB::CGfxWindow::Destroy()
{
	UnregisterClass(mWinClassName.c_str(), mhInstance);

	return eResult::OK;
}

void GFXLIB::CGfxWindow::SwapBuffers()
{
	HDC hDC = GetDC(mhWnd);
	int ret = StretchDIBits(
		hDC,
		0, 0, (int)mWidth, (int)mHeight,
		0, 0, (int)mWidth, (int)mHeight,
		mpBackBuffer,
		&mBitmapInfo,
		DIB_RGB_COLORS,
		SRCCOPY
		);
	DeleteDC(hDC);
}

void GFXLIB::CGfxWindow::ClearBuffer()
{
	memset(mpBackBuffer, 0,(size_t)(mWidth * mHeight * BYTES_PER_PIXEL));
}
