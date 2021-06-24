#include "PlayerController.h"

#include "../XX.h"
#include "../Scenes/Scene.h"
#include "../GameObjects/GameObject.h"
#include "../Components/Components.h"

#include "BulletController.h"




static float cd = 0;

void XX::PlayerController::Update()
{

	if (GetKeyState(VK_UP) & 0x80)
	{
		game_object->transform->position += game_object->transform->Forward() *0.1;
		
	}

	if (GetKeyState(VK_DOWN) & 0x80)
	{
		game_object->transform->position -= game_object->transform->Forward() * 0.1;
		
	}

	if (GetKeyState(VK_LEFT) & 0x80)
	{
		game_object->transform->rotation -= XXVector3(0.0f, 0.02f, 0.0f);
	}

	if (GetKeyState(VK_RIGHT) & 0x80)
	{
		game_object->transform->rotation += XXVector3(0.0f, 0.02f, 0.0f);
	}

	if ((GetKeyState('V') & 0x80) && cd <= 0)
	{
		GameObjectPtr bullet = GameObject::Create();
		{
			bullet->tag = "bullet";
			bullet->transform->scale = { 0.5f,0.5f,0.5f };
			bullet->transform->position = game_object->transform->position + game_object->transform->Forward() * 3 + game_object->transform->Up() * 1;

			auto m = Component::Create<Mesh>("Assets\\models\\torus\\torus.obj");
			bullet->AddComponent(m);

			auto bc = Component::Create < BulletController>();
			bc->dir = game_object->transform->Forward();
			bc->speed = 0.2f;
			bullet->AddComponent(bc);
		}
		game_object->scene->AddGameObject(bullet);
		
		cd = 10;
	}
	cd--;
}
