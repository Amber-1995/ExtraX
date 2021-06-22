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
		camera->transform->rotation = XXVector3(0.5f, 0, 0);

		auto c = Component::Create<Camera>();
		camera->AddComponent(c);

		auto cc = Component::Create <CameraController>();
		camera->AddComponent(cc);
	}
	AddGameObject(camera);

	auto p2d = GameObject::Create();
	{
		p2d->transform->position = XXVector3(50.0f, 50.0f, 0.0f);
		auto s = Component::Create<Sprite2D>(100.0f,100.0f,"Assets\\Textures\\06.jpg");
		p2d->AddComponent(s);
	}
	AddGameObject(p2d);

	auto p3d = GameObject::Create();
	{
		p3d->transform->position = XXVector3(5.0f, 0.0f, 0.0f);
		auto s = Component::Create<Billboard>(10.0f, 10.0f, "Assets\\Textures\\06.jpg");
		p3d->AddComponent(s);
	}
	AddGameObject(p3d);

	GameObjectPtr field = GameObject::Create();
	{
		auto f= Component::Create<Field>(20,20, "Assets\\Textures\\ground.png");
		field->AddComponent(f);
	}
	AddGameObject(field);

	GameObjectPtr player = GameObject::Create();
	{
		player->tag = "player";
		player->transform->position = XXVector3(0, 0, -5);
		auto m= Component::Create< Mesh>("Assets\\models\\torus\\torus.obj");
		player->AddComponent(m);

		/*PlayerControllerPtr pc = Component::Create<PlayerController>();
		player->AddComponent(pc);*/
	}
	AddGameObject(player);

	GameObjectPtr enemy1 = GameObject::Create();
	{
		enemy1->tag = "enemy";
		enemy1->transform->position = XXVector3(0, 0, 5);
		MeshPtr m = Component::Create < Mesh>("Assets\\models\\torus\\torus.obj");
		enemy1->AddComponent(m);
	}
	AddGameObject(enemy1);

	GameObjectPtr enemy2 = GameObject::Create();
	{
		enemy2->tag = "enemy";
		enemy2->transform->position = XXVector3(5, 0, 5);
		MeshPtr m = Component::Create < Mesh>("Assets\\models\\torus\\torus.obj");
		enemy2->AddComponent(m);
	}
	AddGameObject(enemy2);

	GameObjectPtr enemy3 = GameObject::Create();
	{
		enemy3->tag = "enemy";
		enemy3->transform->position = XXVector3(-5, 0, 5);
		MeshPtr m = Component::Create < Mesh>("Assets\\models\\torus\\torus.obj");
		enemy3->AddComponent(m);
	}
	AddGameObject(enemy3);
}
