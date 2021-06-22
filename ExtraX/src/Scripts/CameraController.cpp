#include "CameraController.h"

#include "../XX.h"
#include "../Scenes/Scene.h"
#include "../GameObjects/GameObject.h"
#include "../Components/Components.h"

void XX::CameraController::Update()
{

	if (GetKeyState(VK_UP) & 0x80)
	{
		game_object->transform->position += XXVector3(0.0f, 0.0f, 0.1f);
	}

	if (GetKeyState(VK_DOWN) & 0x80)
	{
		game_object->transform->position -= XXVector3(0.0f, 0.0f, 0.1f);
	}

	if (GetKeyState(VK_LEFT) & 0x80)
	{
		game_object->transform->position -= XXVector3(0.1f, 0.0f, 0.0f);
	}

	if (GetKeyState(VK_RIGHT) & 0x80)
	{
		game_object->transform->position += XXVector3(0.1f, 0.0f, 0.0f);
	}

	if (GetKeyState('Q') & 0x80)
	{
		game_object->transform->rotation -= XXVector3(0.0f, 0.01f, 0.0f);
	}

	if (GetKeyState('E') & 0x80)
	{
		game_object->transform->rotation += XXVector3(0.0f, 0.01f, 0.0f);
	}


}
