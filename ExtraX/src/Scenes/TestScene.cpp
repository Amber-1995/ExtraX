#include "TestScene.h"

#include "../GameObjects/GameObject.h"
#include "../Components/Components.h"
#include "../Scripts/Scripts.h"
#include "../Data/Data.h"

XX::TestScene::TestScene()
{
	//=============================================================================
	auto camera = GameObject::Create();
	auto ground = GameObject::Create();
	auto player = GameObject::Create();





	//=============================================================================
	{
		camera->transform->position = XXVector3(0, 10, -15);
		camera->transform->rotation = XXVector3(0.5f, 0, 0);

		auto c = Component::Create<Camera>();
		camera->AddComponent(c);

		auto cc = Component::Create <CameraController>();
		cc->target = player;
		camera->AddComponent(cc);

		auto skybox = Component::Create<Skybox>();
		skybox->SetTexture(
			"Assets\\Textures\\Skybox\\FluffballDayTop.jpg",
			"Assets\\Textures\\Skybox\\FluffballDayBottom.jpg",
			"Assets\\Textures\\Skybox\\FluffballDayLeft.jpg",
			"Assets\\Textures\\Skybox\\FluffballDayRight.jpg",
			"Assets\\Textures\\Skybox\\FluffballDayFront.jpg",
			"Assets\\Textures\\Skybox\\FluffballDayBack.jpg"
		);
		camera->AddComponent(skybox);
	}
	

	
	{
		auto field = Component::Create<Field>(40, 40);
		ground->AddComponent(field);
	}
	

	
	{
		auto cannon = Component::Create<Mesh>("Assets\\models\\tank0001\\tank0001-0.obj");
		cannon->AdjustTransform({ 0.0f,0.0f,0.0f }, { 0.0f,-DirectX::XM_PIDIV2,0.0f }, { 1.0f,1.0f,1.0f });
		player->AddComponent(cannon);

		auto tank = Component::Create<Mesh>("Assets\\models\\tank0001\\tank0001-1.obj");
		tank->AdjustTransform({ 0.0f,0.0f,0.0f }, { 0.0f,-DirectX::XM_PIDIV2,0.0f }, { 1.0f,1.0f,1.0f });
		player->AddComponent(tank);

		auto pc = Component::Create<PlayerController>();
		player->AddComponent(pc);

	}



	//=========================================================================
	AddGameObject(camera);
	AddGameObject(ground);
	AddGameObject(player);


}
