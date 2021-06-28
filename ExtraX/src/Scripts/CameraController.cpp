#include "CameraController.h"

#include "../XX.h"
#include "../Scenes/Scene.h"
#include "../GameObjects/GameObject.h"
#include "../Components/Components.h"


void XX::CameraController::Start()
{

}


static bool camera_mode = false;

void XX::CameraController::Update()
{
	if (camera_mode) {
		if (ExtraX::input.GetKey(KK_W))
		{
			game_object->transform->position += game_object->GetComponent<Transform>()->Forward() * 0.1f;
		}

		if (ExtraX::input.GetKey(KK_S))
		{
			game_object->transform->position -= game_object->transform->Forward() * 0.1f;
		}

		if (ExtraX::input.GetKey(KK_A))
		{
			game_object->transform->position -= game_object->transform->Right() * 0.1f;
		}

		if (ExtraX::input.GetKey(KK_D))
		{
			game_object->transform->position += game_object->transform->Right() * 0.1f;
		}


		if (ExtraX::input.GetKey(KK_UP))
		{
			game_object->transform->rotation -= XXVector3(0.01f, 0.0f, 0.0f);
		}

		if (ExtraX::input.GetKey(KK_DOWN))
		{
			game_object->transform->rotation += XXVector3(0.01f, 0.0f, 0.0f);
		}

		if (ExtraX::input.GetKey(KK_LEFT))
		{
			game_object->transform->rotation -= XXVector3(0.0f, 0.01f, 0.0f);
		}

		if (ExtraX::input.GetKey(KK_RIGHT))
		{
			game_object->transform->rotation += XXVector3(0.0f, 0.01f, 0.0f);
		}

		if (ExtraX::input.GetKey(KK_F))
		{
			game_object->transform->position += XXVector3(0.0f, 0.1f, 0.0f);
		}

		if (ExtraX::input.GetKey(KK_C))
		{
			game_object->transform->position -= XXVector3(0.0f, 0.1f, 0.0f);
		}
	}
	
	if (!camera_mode) {
		game_object->transform->rotation = player->transform->rotation;
		game_object->transform->position = player->transform->position;

		game_object->transform->rotation += XXVector3(0.5f, 0.0f, 0.0f);
		game_object->transform->position += -player->transform->Forward() * 5 + XXVector3(0.0f, 5.0f, 0.0f);
	}

	if (ExtraX::input.GetKeyDown(KK_P))
	{
		camera_mode = !camera_mode;
		player->SetActive(!camera_mode);
	}
}
