#pragma comment(lib, "tilelibd.lib")

#include "stdafx.h"
#include <Windows.h>

#include "Cell.h"
#include "Point.h"
#include "GameEngine.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	//Set debug flag for mem alloc logging
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	GameEngine engine("Kingdoms of Amalor", 800, 672, "tiles", 32, 3, 64); //25 x 19 tiles

	while (!engine.quitGame())
		engine.run();
}