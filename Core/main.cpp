#include "Common/ExtraX.h"
#include <windows.h>
#include "Common/Graphics.h"
#include "Game/Module.h"
#include <iostream>
#include <condition_variable>
#include <thread>
#include <chrono>
#include <Windows.h>


#include "Game/Components/Polygon2D.h"
#include "Game/Components/Transform.h"
using namespace XX;
using namespace XX::Game;

int main()
{
    ExtraX::Initialize("2333");

	Scene s;

	// ���b�Z�[�W���[�v
	MSG msg;
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				break;
			}
			else
			{
				// ���b�Z�[�W�̖|��ƃf�B�X�p�b�`
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			ExtraX::graphics->Begin();
			s.FramePreprocess();
			s.FrameProcess();
			ExtraX::graphics->End();
		}
	}



    return 0;
}

