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
	TestScene* s = new TestScene();
	s->Awake();
	

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

			XX::ExtraX::renderer3d.Render();

			XX::ExtraX::renderer2d.Render();

			XX::ExtraX::graphics.End();
		}
	}
	return (int)msg.wParam;
}
