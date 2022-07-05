#include "Common/ExtraX.h"
#include <windows.h>
#include "Common/Graphics.h"
#include "Game/Module.h"
#include <iostream>
#include <condition_variable>
#include <thread>
#include <chrono>


#include "Common/Window.h"
#include "Game/Components/Polygon.h"
#include "Game/Components/Transform.h"

using namespace XX;
using namespace XX::Game;

int main()
{
	ExtraX::Initialize("2333", 1);

	Scene s;
	
	ExtraX::window->BindScene(&s);

	ExtraX::window->Run();


    return 0;
}

