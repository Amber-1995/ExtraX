#include "TestScene.h"

#include "../GameObjects/GameObject.h"
#include "../Components/Components.h"
#include "../Scripts/Scripts.h"
#include "../Data/Data.h"

XX::TestScene01::TestScene01()
{
	
	auto camera = GameObject::Create();
	{
		camera->transform->rotation = { -0.5f,-2.5f,0.0f };
		auto c = Component::Create<Camera>();
		camera->AddComponent(c);

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
	AddGameObject(camera);
	

	auto gamestart = GameObject::Create();
	{
		gamestart->transform->position = { 640,360,0 };
		auto b = Component::Create<Sprite2D>(500.0f, 250.0f, "Assets\\Textures\\game start 0.png");
		gamestart->AddComponent(b);
		auto ac = Component::Create<Animation2D>();
		ac->SetTarget(b);
		ac->AddAnimationClip("Assets\\Textures\\game start 0.png", 1, 1, "0", 0, 0, true, "0");
		ac->AddAnimationClip("Assets\\Textures\\game start 1.png", 1, 1, "1", 0, 0, true, "1");
		ac->SetEnterAnimation("0");
		gamestart->AddComponent(ac);
		auto sb = Component::Create<StartButton>();
		gamestart->AddComponent(sb);
	}
	AddGameObject(gamestart);

}

XX::TestScene02::TestScene02()
{

	auto ground = GameObject::Create();
	{
		auto f = Component::Create <Field>(40, 40);
		ground->AddComponent(f);
	}
	AddGameObject(ground);

	auto w0 = GameObject::Create();
	{
		w0->transform->rotation = { 0.0f,0.0f,0.0f };
		w0->transform->position = { 0.0f,5.0f,20.0f };
		auto s = Component::Create <Sprite3D>(40, 10, "Assets\\Textures\\ground.png");
		w0->AddComponent(s);
	}
	AddGameObject(w0);

	auto w1 = GameObject::Create();
	{
		w1->transform->rotation = { 0.0f,DirectX::XM_PI,0.0f };
		w1->transform->position = { 0.0f,5.0f,-20.0f };
		auto s = Component::Create <Sprite3D>(40, 10, "Assets\\Textures\\ground.png");
		w1->AddComponent(s);
	}
	AddGameObject(w1);


	auto w2 = GameObject::Create();
	{
		w2->transform->rotation = { 0.0f,DirectX::XM_PIDIV2,0.0f };
		w2->transform->position = { 20.0f,5.0f,0.0f };
		auto s = Component::Create <Sprite3D>(40, 10, "Assets\\Textures\\ground.png");
		w2->AddComponent(s);
	}
	AddGameObject(w2);
	auto w3 = GameObject::Create();
	{
		w3->transform->rotation = { 0.0f,-DirectX::XM_PIDIV2,0.0f };
		w3->transform->position = { -20.0f,5.0f,0.0f };
		auto s = Component::Create <Sprite3D>(40, 10, "Assets\\Textures\\ground.png");
		w3->AddComponent(s);
	}
	AddGameObject(w3);

	auto player = GameObject::Create();
	{
		auto m = Component::Create <Model>("Assets\\models\\tank0002\\tank0002.obj");
		m->AdjustTransform(
			{ 0.0f,0.0f,0.0f },
			{ 0.0f,DirectX::XM_PI,0.0f },
			{ 0.5f,0.5f,0.5f }
		);
		player->AddComponent(m);
		auto pc = Component::Create <PlayerController>();
		player->AddComponent(pc);
	}
	AddGameObject(player);

	auto camera = GameObject::Create();
	{
		camera->transform->position = { 0.5f,0.0f,0.0f };
		camera->transform->position = { 0.0f,10.0f,-15.0f };
		auto c = Component::Create<Camera>();
		camera->AddComponent(c);

		auto cc = Component::Create <CameraController>();
		cc->player = player;
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
	AddGameObject(camera);

}
