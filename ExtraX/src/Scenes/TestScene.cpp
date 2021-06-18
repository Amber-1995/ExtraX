#include "TestScene.h"
#include "../Scripts/Scripts.h"
#include "../GameObjects/GameObject.h"
#include "../Components/Components.h"


XX::TestScene::TestScene()
{
	GameObject* camera = new GameObject();
	{
		camera->transform->position = XXVector3(0, 10, -15);
		Camera* c = new Camera();
		camera->AddComponent(c);

		PlayerController* pc = new PlayerController();
		camera->AddComponent(pc);
	}
	AddGameObject(camera);

	GameObject* p2d = new GameObject();
	{
		Sprite* s = new Sprite();
		p2d->AddComponent(s);
	}
	AddGameObject(p2d);


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
