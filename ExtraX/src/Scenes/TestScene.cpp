#include "TestScene.h"

#include "../GameObjects/GameObject.h"
#include "../Components/Components.h"
#include "../Scripts/Scripts.h"
#include "../Data/Data.h"

XX::TestScene::TestScene()
{
	auto camera = GameObject::Create();
	{
		camera->transform->position = XXVector3(0, 10, -15);
		camera->transform->rotation = XXVector3(0.5, 0, 0);

		auto c = Component::Create<Camera>();
		camera->AddComponent(c);
	}
	AddGameObject(camera);

	auto p2d = GameObject::Create();
	{
		p2d->transform->position = XXVector3(100, 100, 0.5);
		auto s = Component::Create<Sprite>();
		p2d->AddComponent(s);
	}
	AddGameObject(p2d);

	auto p2d2 = GameObject::Create();
	{
		p2d2->transform->position = XXVector3(150, 150, 1);
		auto s = Component::Create<Sprite>();
		p2d2->AddComponent(s);
	}
	AddGameObject(p2d2);


	GameObjectPtr field = GameObject::Create();
	{
		auto f= Component::Create<Field>();
		field->AddComponent(f);
	}
	AddGameObject(field);

	GameObjectPtr player = GameObject::Create();
	{
		player->tag = "player";
		player->transform->position = XXVector3(0, 0, -5);
		auto m= Component::Create< Mesh>("Assets\\models\\torus\\torus.obj");
		player->AddComponent(m);

		PlayerControllerPtr pc(new PlayerController());
		player->AddComponent(pc);
	}
	AddGameObject(player);

	/*GameObjectPtr enemy1(new GameObject());
	{
		enemy1->tag = "enemy";
		enemy1->transform->position = XXVector3(0, 0, 5);
		MeshPtr m(new Mesh("Assets\\models\\torus\\torus.obj"));
		enemy1->AddComponent(m);
	}
	AddGameObject(enemy1);

	GameObjectPtr enemy2(new GameObject());
	{
		enemy2->tag = "enemy";
		enemy2->transform->position = XXVector3(5, 0, 5);
		MeshPtr m(new Mesh("Assets\\models\\torus\\torus.obj"));
		enemy2->AddComponent(m);
	}
	AddGameObject(enemy2);

	GameObjectPtr enemy3(new GameObject());
	{
		enemy3->tag = "enemy";
		enemy3->transform->position = XXVector3(-5, 0, 5);
		MeshPtr m(new Mesh("Assets\\models\\torus\\torus.obj"));
		enemy3->AddComponent(m);
	}
	AddGameObject(enemy3);*/
}
