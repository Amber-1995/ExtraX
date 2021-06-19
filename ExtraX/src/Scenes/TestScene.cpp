#include "TestScene.h"

#include "../GameObjects/GameObject.h"
#include "../Components/Components.h"
#include "../Scripts/Scripts.h"

XX::TestScene::TestScene()
{
	GameObject* camera = new GameObject();
	{
		camera->transform->position = XXVector3(0, 10, -15);
		camera->transform->rotation = XXVector3(0.5, 0, 0);
		Camera* c = new Camera();
		camera->AddComponent(c);
	}
	AddGameObject(camera);

	GameObject* p2d = new GameObject();
	{
		p2d->transform->position = XXVector3(100, 100, 1);
		Sprite* s = new Sprite();
		p2d->AddComponent(s);
	}
	AddGameObject(p2d);

	GameObject* p2d2 = new GameObject();
	{
		p2d2->transform->position = XXVector3(150, 150, 0.5);
		Sprite* s = new Sprite();
		p2d2->AddComponent(s);
	}
	AddGameObject(p2d2);


	GameObject* field = new GameObject();
	{
		Field* f = new Field();
		field->AddComponent(f);
	}
	AddGameObject(field);

	GameObject* player = new GameObject();
	{
		player->tag = "player";
		player->transform->position = XXVector3(0, 0, -5);
		Mesh* m = new Mesh("Assets\\models\\torus\\torus.obj");
		player->AddComponent(m);

		PlayerController* pc = new PlayerController();
		player->AddComponent(pc);
	}
	AddGameObject(player);

	GameObject* enemy1 = new GameObject();
	{
		enemy1->tag = "enemy";
		enemy1->transform->position = XXVector3(0, 0, 5);
		Mesh* m = new Mesh("Assets\\models\\torus\\torus.obj");
		enemy1->AddComponent(m);
	}
	AddGameObject(enemy1);

	GameObject* enemy2 = new GameObject();
	{
		enemy2->tag = "enemy";
		enemy2->transform->position = XXVector3(5, 0, 5);
		Mesh* m = new Mesh("Assets\\models\\torus\\torus.obj");
		enemy2->AddComponent(m);
	}
	AddGameObject(enemy2);

	GameObject* enemy3 = new GameObject();
	{
		enemy3->tag = "enemy";
		enemy3->transform->position = XXVector3(-5, 0, 5);
		Mesh* m = new Mesh("Assets\\models\\torus\\torus.obj");
		enemy3->AddComponent(m);
	}
	AddGameObject(enemy3);
}
