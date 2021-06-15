#include "PlayerController.h"
#include "../GameObjects/GameObject.h"
#include "../Components/Transform.h"
#include "BulletController.h"
#include "../Scenes//Scene.h"
#include "../Components/Model.h"


static float cd = 0;

void XX::PlayerController::Update()
{

	if (GetKeyState(VK_UP) & 0x80)
	{
		game_object->transform->position.z += 0.1f;
	}

	if (GetKeyState(VK_DOWN) & 0x80)
	{
		game_object->transform->position.z -= 0.1f;
	}

	if (GetKeyState(VK_LEFT) & 0x80)
	{
		game_object->transform->position.x -= 0.1f;
	}

	if (GetKeyState(VK_RIGHT) & 0x80)
	{
		game_object->transform->position.x += 0.1f;
	}

	if ((GetKeyState('W') & 0x80) && cd <= 0)
	{
		GameObject* bullet = new GameObject();
		{
			bullet->tag = "bullet";
			bullet->transform->scale = { 0.5f,0.5f,0.5f };
			bullet->transform->position = game_object->transform->position;
			Model* m = new Model("Assets\\models\\torus\\torus.obj");
			bullet->AddComponent(m);

			BulletController* bc = new BulletController();
			bullet->AddComponent(bc);
		}
		game_object->scene->AddGameObject(bullet);
		
		cd = 10;
	}

	cd -= 1;
}
