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
	_scene = ScenePtr(new TestScene01());
	_next_scene = _scene;
	_scene->Spawn();
	

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

			XX::ExtraX::input.Update();

			XX::ExtraX::graphics.Begin();

			XX::ExtraX::renderer3d.Render();

			XX::ExtraX::renderer2d.Render();

			XX::ExtraX::graphics.End();

			if (_scene != _next_scene)
			{
				_scene->Destroy();
				_scene = _next_scene;
				_scene->Spawn();
			}
		}
	}
	return (int)msg.wParam;
}

void XX::Game::NextScene(ScenePtr scene)
{
	_next_scene = scene;
}
