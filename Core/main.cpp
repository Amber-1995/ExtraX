#include "Common/ExtraX.h"
#include <windows.h>
#include "Common/Graphics.h"
#include "Game/Module.h"
#include <iostream>
#include <condition_variable>
#include <thread>
#include <chrono>
#include <Windows.h>


#include "Game/Components/Polygon.h"
#include "Game/Components/Transform.h"
using namespace XX;
using namespace XX::Game;

int main()
{
    ExtraX::Initialize("2333");

	Scene s;
	s.Start();

	GameObject* g = s.AddGameObject<GameObject>();
	g->AddComponent<Components::Transform>();
	g->AddComponent<Components::Rect2D>();

	// メッセージループ
	MSG msg;
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{// PostQuitMessage()が呼ばれたらループ終了
				break;
			}
			else
			{
				// メッセージの翻訳とディスパッチ
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			s.Run();
		}
	}



    return 0;
}

