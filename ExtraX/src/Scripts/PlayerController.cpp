#include "PlayerController.h"

#include "../XX.h"
#include "../Scenes/Scene.h"
#include "../GameObjects/GameObject.h"
#include "../Components/Components.h"

#include "BulletController.h"





void XX::PlayerController::Update()
{

	if (ExtraX::input.GetKey(KK_UP))
	{
		game_object->transform->position += game_object->transform->Forward() *0.1f;
		
	}

	if (ExtraX::input.GetKey(KK_DOWN))
	{
		game_object->transform->position -= game_object->transform->Forward() * 0.1f;
		
	}

	if (ExtraX::input.GetKey(KK_LEFT))
	{
		game_object->transform->rotation -= XXVector3(0.0f, 0.02f, 0.0f);
	}

	if (ExtraX::input.GetKey(KK_RIGHT))
	{
		game_object->transform->rotation += XXVector3(0.0f, 0.02f, 0.0f);
	}

	if (ExtraX::input.GetKeyDown(KK_SPACE))
	{
		GameObjectPtr bullet = GameObject::Create();
		{
			bullet->tag = "bullet";
			bullet->transform->scale = { 0.5f,0.5f,0.5f };
			bullet->transform->position = game_object->transform->position + game_object->transform->Forward() * 3 + game_object->transform->Up() * 1;

			auto m = Component::Create<Model>("Assets\\models\\torus\\torus.obj");
			bullet->AddComponent(m);

			auto bc = Component::Create < BulletController>();
			bc->dir = game_object->transform->Forward();
			bc->speed = 0.2f;
			bullet->AddComponent(bc);
		}
		game_object->scene->AddGameObject(bullet);
		
	}


	if (game_object->transform->position.x > 19)
	{
		XXVector3 temp = game_object->transform->position;
		temp.x = 19;
		game_object->transform->position = temp;
	}
	if (game_object->transform->position.x < -19)
	{
		XXVector3 temp = game_object->transform->position;
		temp.x = -19;
		game_object->transform->position = temp;
	}
	if (game_object->transform->position.z > 19)
	{
		XXVector3 temp = game_object->transform->position;
		temp.z = 19;
		game_object->transform->position = temp;
	}
	if (game_object->transform->position.z < -19)
	{
		XXVector3 temp = game_object->transform->position;
		temp.z = -19;
		game_object->transform->position = temp;
	}


}
