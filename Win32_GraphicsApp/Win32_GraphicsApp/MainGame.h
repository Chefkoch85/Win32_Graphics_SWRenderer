#pragma once

#include <GfxLib\IGame.h>

#include <Windows.h>

#include <vector>

#include "Block.h"
#include "Player.h"

class CMainGame : public GFXLIB::IGame
{
public:
	static CMainGame* Instance();
	~CMainGame();

protected:
	CMainGame();
	static LRESULT CALLBACK WindowCallback(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	// Geerbt über IGame
	virtual LRESULT WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	virtual GFXLIB::eResult onInit(HINSTANCE hInstance, LPSTR lpCmdLine) override;
	virtual GFXLIB::eResult onExit() override;

	virtual void Update(float dt) override;
	virtual void Render() override;

protected:
	static CMainGame* mInstance;

	float mRow = 0;
	bool mRunLine = false;
	std::vector<CBlock> mGround;
	int mNumSprites = 100;
	CPlayer mPlayer;
};

