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
		game_object->transform->position += XXVector3(0.0f,0.0f,0.1f);
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

	if ((GetKeyState('W') & 0x80) && cd <= 0)
	{
		GameObjectPtr bullet = GameObject::Create();
		{
			bullet->tag = "bullet";
			bullet->transform->scale = { 0.5f,0.5f,0.5f };
			bullet->transform->position = game_object->transform->position;

			auto m = Component::Create<Mesh>("Assets\\models\\torus\\torus.obj");
			bullet->AddComponent(m);

			auto bc = Component::Create < BulletController>();
			bullet->AddComponent(bc);
		}
		game_object->scene->AddGameObject(bullet);
		
		cd = 10;
	}

	if ((GetKeyState('Q') & 0x80) && cd <= 0)
	{
		static bool state = true;
		ExtraX::graphics.SetFullscreenState(state);
		state = !state;
	}

	cd -= 1;
}
