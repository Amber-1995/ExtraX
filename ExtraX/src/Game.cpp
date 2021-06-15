#include "Game.h"
#include <Windows.h>
#include "XX.h"
#include "Scenes/TestScene.h"


XX::Game::Game()
{
}

XX::Game::~Game()
{
}



int XX::Game::Run()
{
	
	new TestScene();

	

	MSG msg{};
	while (1) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {
				break;
			}
			else {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else {

			XX::ExtraX::updater.Update();

			XX::ExtraX::graphics.Begin();

			XX::ExtraX::renderer.Render();

			XX::ExtraX::graphics.End();
		}
	}
	return (int)msg.wParam;
}
