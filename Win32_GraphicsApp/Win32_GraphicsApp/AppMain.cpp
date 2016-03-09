
#include "MainGame.h"

int WINAPI WinMain(HINSTANCE hInstance,	HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	GFXLIB::eResult result = GFXLIB::eResult::OK;

	CMainGame* game = CMainGame::Instance();

	if ((result = game->GameInit(hInstance, lpCmdLine)) != GFXLIB::eResult::OK)
		return (int)result;
	
	if ((result = game->GameLoop()) != GFXLIB::eResult::OK)
		return (int)result;

	if ((result = game->GameExit()) != GFXLIB::eResult::OK)
		return (int)result;

	return (int)result;
}